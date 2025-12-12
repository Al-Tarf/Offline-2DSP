#ifndef OFFLINE2DSP_H
#define OFFLINE2DSP_H

#include <QObject>
#include <QVector>
#include <QRect>

class Offline2DSP : public QObject
{
    Q_OBJECT

signals:
    void signalRepaintResult(); // Сигнал для отправки события перерисовки окна

public slots:
    void slotRunCalculate();    // Слот выполняющий вычисления

public:
    explicit Offline2DSP(QObject *parent = nullptr, uint uiWidth = 0, uint uiHeight = 0);
    ~Offline2DSP();

    struct Stripe {
        QRect   qrMeasurements; // Размеры одного изделия
        uint    uiQuantity;     // Количество изделий такого размера
    }stripe; // Буфер для данных для временного хранения информации об одном типе изделий

    QRect               Sheet;      // Переменная с размерами листа
    QVector<Stripe>     Products;   // Вектор с информацией об изделиях
    QVector<QRect>      Result;     // Вектор с результатами расчёта

private:
// Буфер для промежуточного хранения данных:
    struct Buffer {
        QVector<QRect>  other;          // Вектор для изделий шире ширины листа-заготовки (шире 100%)
        QVector<QRect>  width_67_100;   // Вектор для изделий шире 2/3 (67%) ширины листа-заготовки
        QVector<QRect>  width_51_66;    // Вектор для изделий шире 1/2 (50%) но уже 2/3 (67%) ширины листа-заготовки
        QVector<QRect>  width_0_50;     // Вектор для изделий уже 1/2 (50%) ширины листа-заготовки
    }buffer;
};

#endif // OFFLINE2DSP_H
