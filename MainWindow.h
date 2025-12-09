#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPainter>

#include "ProductsDialog.h"
#include "SheetDialog.h"
#include "Offline2DSP.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Класс главного окна приложения:
class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void signalRunCalculate(); // Сигнал запуска вычислений

public slots:
// Слоты забирающие данные из диалоговых окон и посылающие сигнал на запуск вычислений:
    void slotProductsDataReady(QTableWidget* pqtv);         // Данные по типам изделий и их количеству можно забирать
    void slotSheetDataReady(qreal qWidth, qreal qHeight);   // Данные о листе-заготовке можно забирать
// Слот посылающий событие отрисовки окна:
    void slotRepaintResult();
// Слоты отображающие диалоговые окна:
    void slotShowProductsDialog();
    void slotShowSheetDialog();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event); //Обработчик события отрисовки окна

private:
// Указатели на диалоги:
    ProductsDialog  *productsdialog;
    SheetDialog     *sheetdialog;
// Указатель на объект, получающий исходные данные, производящий расчёты и хранящий их результат
    Offline2DSP     *o2dsp;

    Ui::MainWindow  *ui;
};
#endif // MAINWINDOW_H
