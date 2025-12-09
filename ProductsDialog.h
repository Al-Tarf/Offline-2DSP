#ifndef PRODUCTSDIALOG_H
#define PRODUCTSDIALOG_H

#define BTN_CANCEL (QDialogButtonBox::Cancel)
#define BTN_APPLY  (QDialogButtonBox::Apply)
#define BTN_RESET  (QDialogButtonBox::Reset)

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QTableWidget>

namespace Ui {
class productsDialog;
}

// Перечисление с индексами столбцов таблицы:
enum {
    eColumnIndex_Width,
    eColumnIndex_Height,
    eColumnIndex_Quantity,
    eColumnIndex_Total
};

class ProductsDialog : public QDialog
{
    Q_OBJECT

signals:
    void signalProductsDataReady(QTableWidget* pqtv);   // Сигнал запускающий передачу данных из диалога "Изделия"

private slots:
    void slotButtonClicked(QAbstractButton *button);    // Слот обрабатывающий нажатия кнопок диалога
    void slotProdtypesnumValueChanged(int value);       // Слот обрабатывающий изменение в поле-счётчике количества типов изделий
    void slotProdlistCellChanged(int row, int column);  // Слот обрабатывающий изменение данных в ячейках таблицы

public:
    explicit ProductsDialog(QWidget *parent = nullptr);
    ~ProductsDialog();

private:
    void CheckCellData();   // Метод проверяющий все ли ячейки таблицы заполнены значениями

    Ui::productsDialog *ui;
};

#endif // PRODUCTSDIALOG_H

