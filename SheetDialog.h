#ifndef SHEETDIALOG_H
#define SHEETDIALOG_H

#define BTN_CANCEL (QDialogButtonBox::Cancel)
#define BTN_APPLY  (QDialogButtonBox::Apply)
#define BTN_RESET  (QDialogButtonBox::Reset)

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class sheetDialog;
}

class SheetDialog : public QDialog
{
    Q_OBJECT

signals:
// Сигнал запускающий передачу данных из диалога "Листы-заготовки":
    void signalSheetDataReady(qreal lenghth, qreal width);

private slots:
    void slotButtonClicked(QAbstractButton *button);            // Слот обрабатывающий нажатия кнопок диалога
// Слоты обрабатывающие изменения значений в полях-счётчиках диалога:
    void slotSheetlengthValueChanged(double sheetlength_value); // Длина листа-заготовки
    void slotSheetwidthValueChanged(double sheetwidth_value);   // Ширина листа-заготовки

public:
    explicit SheetDialog(QWidget *parent = nullptr);
    ~SheetDialog();

private:
    Ui::sheetDialog *ui;
};

#endif // SHEETDIALOG_H
