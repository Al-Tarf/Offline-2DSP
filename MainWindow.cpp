#include "MainWindow.h"
#include "ui_MainWindow.h"

// Конструктор:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    productsdialog  = new ProductsDialog(this); // Диалог "Изделия"
    sheetdialog     = new SheetDialog(this);    // Диалог "Листы-заготовки"
    _2dsp           = new _2DSP(this, 0, 0);    // Объект проводящий расчёты

// Соединяем сигналы и слоты меню:
    QObject::connect(ui->productsaction, &QAction::triggered, this, &MainWindow::slotShowProductsDialog);
    QObject::connect(ui->sheetaction,   &QAction::triggered, this, &MainWindow::slotShowSheetDialog);

// Соединяем сигналы и слоты для передачи данных из диалогов:
    QObject::connect(productsdialog, &ProductsDialog::signalProductsDataReady, this, &MainWindow::slotProductsDataReady);
    QObject::connect(sheetdialog, &SheetDialog::signalSheetDataReady, this, &MainWindow::slotSheetDataReady);

// Соединяем сигналы и слоты предназначенные для расчёта и вывода результата:
    QObject::connect(this, &MainWindow::signalRunCalculate, _2dsp, &_2DSP::slotRunCalculate);
    QObject::connect(_2dsp, &_2DSP::signalRepaintResult, this, &MainWindow::slotRepaintResult);
}

// Деструктор:
MainWindow::~MainWindow()
{
    delete productsdialog;
    delete sheetdialog;

    delete _2dsp;

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
   _2dsp->Products.clear();

// И забираем новые данные из таблицы проверяя их на корректность:
    for (int row = 0; row < pQTW->rowCount(); ++row) {
        dValue = pQTW->item(row, eColumnIndex_Lenghth)->text().toDouble(&bOK);
        if ( bOK || (0 < dValue)) _2dsp->stripe.qrMeasurements.setX(dValue);
            else continue;
        dValue = pQTW->item(row, eColumnIndex_Width)->text().toDouble(&bOK);
            if ( bOK || (0 < dValue)) _2dsp->stripe.qrMeasurements.setY(dValue);
            else continue;
        nValue = pQTW->item(row, eColumnIndex_Quantity)->text().toUInt(&bOK);
            if ( bOK || (0 < nValue)) _2dsp->stripe.uiQuantity = nValue;
            else continue;

        _2dsp->Products.push_back(_2dsp->stripe);
    }

// Посылаем сигнал на вычисление если в таблице есть осмысленные данные:
    if (_2dsp->Products.size()) emit signalRunCalculate();
}

// Слот забирающий данные из диалогового окна с параметрами листа-заготовки:
void MainWindow::slotSheetDataReady(qreal lenghth, qreal width) {
        _2dsp->Sheet.setX(lenghth);
        _2dsp->Sheet.setY(width);

// Посылаем сигнал на вычисление если в диалоге есть осмысленные данные:
        if (!lenghth && !width) emit signalRunCalculate();
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

    // Тестовый участок кода ->
    _2dsp->Result.push_back(QRect(50, 50, 500, 500));
    // <- Тестовый участок кода

    painter.drawRects(_2dsp->Result);
}
