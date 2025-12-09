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
    void signalSheetDataReady(qreal qWidth, qreal qHeight);

private slots:
    void slotButtonClicked(QAbstractButton *button);            // Слот обрабатывающий нажатия кнопок диалога
// Слоты обрабатывающие изменения значений в полях-счётчиках диалога:
    void slotSheetwidthValueChanged(double dSheetwidthValue);   // Длина листа-заготовки
    void slotSheetheightValueChanged(double dSheetheightValue); // Ширина листа-заготовки

public:
    explicit SheetDialog(QWidget *parent = nullptr);
    ~SheetDialog();

private:
    Ui::sheetDialog *ui;
};

#endif // SHEETDIALOG_H
