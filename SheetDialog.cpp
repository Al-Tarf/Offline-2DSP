#include "SheetDialog.h"
#include "ui_SheetDialog.h"

// Конструктор:
SheetDialog::SheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sheetDialog)
{
    ui->setupUi(this);

    ui->sheet_buttonBox->button(BTN_APPLY)->setDisabled(true);

// Соединяем сигналы и слоты для обработки событий от элементов управления диалога:
    connect(ui->sheet_buttonBox, &QDialogButtonBox::clicked, this, &SheetDialog::slotButtonClicked);
    connect(ui->sheetlength, &QDoubleSpinBox::valueChanged, this, &SheetDialog::slotSheetlengthValueChanged);
    connect(ui->sheetwidth, &QDoubleSpinBox::valueChanged, this, &SheetDialog::slotSheetwidthValueChanged);
}

// Деструктор:
SheetDialog::~SheetDialog()
{
    delete ui;
}

// Слот обрабатывающий нажатия на кнопки диалога:
void SheetDialog::slotButtonClicked(QAbstractButton *button) {
    if (nullptr == button) return;

    const QDialogButtonBox::StandardButton
            ClickedButton = ui->sheet_buttonBox->standardButton(button);

    switch (ClickedButton) {
    case BTN_CANCEL:
        this->hide();
        break;
    case BTN_APPLY:
        this->hide();
        emit signalSheetDataReady(ui->sheetlength->value(), ui->sheetwidth->value());
        break;
    case BTN_RESET:
        ui->sheetlength->setValue(0);
        ui->sheetwidth->setValue(0);
        break;
    default: // Секция добавлена для подавления предупреждений компилятора
        break;
    }
}

// Слот обрабатывающий изменения значения в поле-счётчике "Длина листа-заготовки":
void SheetDialog::slotSheetlengthValueChanged(double sheetlength_value) {
// Если где нибудь в диалоге есть значение равное 0 кнопка "Применить" будет неактивна:
    ui->sheet_buttonBox->button(BTN_APPLY)->setEnabled((0 < sheetlength_value) && (0 < ui->sheetwidth->value()));
}

// Слот обрабатывающий изменения значения в поле-счётчике диалога "Ширина листа-заготовки":
void SheetDialog::slotSheetwidthValueChanged(double sheetwidth_value) {
// Если где нибудь в диалоге есть значение равное 0 кнопка "Применить" будет неактивна:
    ui->sheet_buttonBox->button(BTN_APPLY)->setEnabled((0 < sheetwidth_value) && (0 < ui->sheetlength->value()));
}

