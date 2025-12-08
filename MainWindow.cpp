#include "MainWindow.h"
#include "ui_MainWindow.h"

// Конструктор:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    productsdialog  = new ProductsDialog(this);     // Диалог "Изделия"
    sheetdialog     = new SheetDialog(this);        // Диалог "Листы-заготовки"
    o2dsp           = new Offline2DSP(this, 0, 0);  // Объект проводящий расчёты

// Соединяем сигналы и слоты меню:
    QObject::connect(ui->productsaction, &QAction::triggered, this, &MainWindow::slotShowProductsDialog);
    QObject::connect(ui->sheetaction,   &QAction::triggered, this, &MainWindow::slotShowSheetDialog);

// Соединяем сигналы и слоты для передачи данных из диалогов:
    QObject::connect(productsdialog, &ProductsDialog::signalProductsDataReady, this, &MainWindow::slotProductsDataReady);
    QObject::connect(sheetdialog, &SheetDialog::signalSheetDataReady, this, &MainWindow::slotSheetDataReady);

// Соединяем сигналы и слоты предназначенные для расчёта и вывода результата:
    QObject::connect(this, &MainWindow::signalRunCalculate, o2dsp, &Offline2DSP::slotRunCalculate);
    QObject::connect(o2dsp, &Offline2DSP::signalRepaintResult, this, &MainWindow::slotRepaintResult);
}

// Деструктор:
MainWindow::~MainWindow()
{
    delete productsdialog;
    delete sheetdialog;

    delete o2dsp;

    delete ui;
}

void MainWindow::slotShowProductsDialog() {
    productsdialog->show();
}

void MainWindow::slotShowSheetDialog() {
    sheetdialog->show();
}

// Слот, забирающий данные из таблицы, и посылающий сигнал на запуск вычислений:
void MainWindow::slotProductsDataReady(QTableWidget* pQTW) {
    if (nullptr == pQTW) return; // Выходим если указатель на таблицу не получен

    bool            bOK     = false;
    double          dValue  = 0;
    int             nValue  = 0;

// Очищаем вектор с исходными данными об изделиях:
   o2dsp->Products.clear();

// И забираем новые данные из таблицы проверяя их на корректность:
    for (int row = 0; row < pQTW->rowCount(); ++row) {
        dValue = pQTW->item(row, eColumnIndex_Length)->text().toDouble(&bOK);
        if ( bOK || (0 < dValue)) o2dsp->stripe.qrMeasurements.setX(uint(dValue * 10)); // Перевод в миллиметры для удобства вычислений
            else continue;
        dValue = pQTW->item(row, eColumnIndex_Width)->text().toDouble(&bOK);
            if ( bOK || (0 < dValue)) o2dsp->stripe.qrMeasurements.setY(uint(dValue * 10)); // Перевод в миллиметры для удобства вычислений
            else continue;
        nValue = pQTW->item(row, eColumnIndex_Quantity)->text().toUInt(&bOK);
            if ( bOK || (0 < nValue)) o2dsp->stripe.uiQuantity = nValue;
            else continue;

        o2dsp->Products.push_back(o2dsp->stripe);
    }

// Посылаем сигнал на вычисление если в таблице есть осмысленные данные:
    if (o2dsp->Products.size()) emit signalRunCalculate();
}

// Слот забирающий данные из диалогового окна с параметрами листа-заготовки:
void MainWindow::slotSheetDataReady(qreal qLength, qreal qWidth) {
    o2dsp->Sheet.setX(uint(qLength * 1000)); // Перевод в миллиметры для удобства вычислений
    o2dsp->Sheet.setY(uint(qWidth * 1000)); // Перевод в миллиметры для удобства вычислений

// Посылаем сигнал на вычисление если в диалоге есть осмысленные данные:
        if (qLength && qWidth) emit signalRunCalculate();
}

// Слот посылающий событие отрисовки окна:
void MainWindow::slotRepaintResult() {
    repaint();
}

//Обработчик события отрисовки окна:
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QColor(Qt::white));

    painter.drawRect(o2dsp->Sheet);
//-> Тестовый код
    for (uint i=100; i<500; i+=100) o2dsp->Result.push_back(QRect(i/10, i/20, i, i/2));
//<- Тестовый код
    if (o2dsp->Result.size()) painter.drawRects(o2dsp->Result);
}
