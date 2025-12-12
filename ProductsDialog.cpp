#include "ProductsDialog.h"
#include "ui_ProductsDialog.h"

// Конструктор:
ProductsDialog::ProductsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productsDialog) {
    ui->setupUi(this);

    QStringList qsl { "Ширина (см.)", "Высота (см.)", "Количество (шт.)" };

    ui->prodlist->setHorizontalHeaderLabels(qsl);

    ui->products_buttonBox->button(BTN_APPLY)->setDisabled(true);

    // Соединяем сигналы и слоты для обработки событий от элементов управления диалога:
    connect(ui->products_buttonBox, &QDialogButtonBox::clicked, this, &ProductsDialog::slotButtonClicked);      // Кнопки
    connect(ui->prodtypesnum, &QSpinBox::valueChanged, this, &ProductsDialog::slotProdtypesnumValueChanged);    // Поле ввода количества типов изделий
    connect(ui->prodlist, &QTableWidget::cellChanged, this, &ProductsDialog::slotProdlistCellChanged);          // Значение ячейки в таблице измененилось
}

// Деструктор:
ProductsDialog::~ProductsDialog() {
    delete ui;
}

// Слот обрабатывающий нажатия на кнопки диалога:
void ProductsDialog::slotButtonClicked(QAbstractButton *button) {
    if (nullptr == button) return;

    const QDialogButtonBox::StandardButton
            ClickedButton = ui->products_buttonBox->standardButton(button);

    switch (ClickedButton) {
    case BTN_CANCEL:
        this->hide();
        break;
    case BTN_APPLY:
        emit signalProductsDataReady(ui->prodlist);
        this->hide();
        break;
    case BTN_RESET:
        ui->prodlist->clearContents();
        ui->prodtypesnum->setValue(1);
        ui->prodlist->setRowCount(1);
        break;
    default: // Секция добавлена для подавления предупреждений компилятора
        break;
    }
}

// Слот обрабатывающий событие изменения значения в поле-счётчике "Количество типов изделий":
void ProductsDialog::slotProdtypesnumValueChanged(int value) {
    ui->prodlist->setRowCount(value);
    CheckCellData();
}

// Слот обрабатывающий событие изменения значения ячеек:
void ProductsDialog::slotProdlistCellChanged(int row, int column) {
    bool    bOK = false;
    double  dValue;

    switch (column) {
    case eColumnIndex_Width:
    case eColumnIndex_Height:
        dValue = ui->prodlist->item(row, column)->text().toDouble(&bOK);
        if ((!bOK) || (dValue < 0.1)) {
            ui->prodlist->item(row, column)->setText("0.0");
        }
        break;
    case eColumnIndex_Quantity:
        ui->prodlist->item(row, column)->text().toUInt(&bOK);
        if (!bOK) {
            ui->prodlist->item(row, column)->setText("0");
        }
        break;
    }

    CheckCellData();
}

// Метод проверяющий все ли ячейки таблицы заполнены значениями:
void ProductsDialog::CheckCellData() {
    QString qsText;
    bool    bOK = true;

    for (int row = 0; row < ui->prodlist->rowCount(); ++row) {
        for (int col = 0; col < eColumnIndex_Total; ++col) {
            if ( nullptr == ui->prodlist->item(row, col) ) bOK = false;
            else {
                qsText.clear();
                qsText.append(ui->prodlist->item(row, col)->text());
/* Ниже используется if, а не присваивание значения логического выражения переменной bOK,
 * чтобы bOK не стало true если последняя ячейка при проходе будет заполнена ненулевым значением */
                if ( !qsText.compare("0"  , Qt::CaseSensitive)
                  || !qsText.compare("0.0", Qt::CaseSensitive) ) bOK = false;
            }
        }
    }

    // Делаем кнопку "Применить" активной если заполнены все ячейки таблицы и неактивной в противном случае:
    ui->products_buttonBox->button(BTN_APPLY)->setEnabled(bOK);
}
