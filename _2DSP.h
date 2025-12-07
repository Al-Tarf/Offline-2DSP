#ifndef _2DSP_H
#define _2DSP_H

#include <QObject>
#include <QVector>
#include <QRect>

class _2DSP : public QObject
{
    Q_OBJECT

signals:
    void signalRepaintResult(); // Сигнал для отправки события перерисовки окна

public slots:
    void slotRunCalculate();    // Слот выполняющий вычисления

public:
    explicit _2DSP(QObject *parent = nullptr, uint uiLenghth = 0, uint uiWidth = 0);
    ~_2DSP();

    struct Stripe {
        QRect   qrMeasurements; // Размеры одного изделия
        uint    uiQuantity;     // Количество изделий такого размера
    }stripe; // Буфер для данных для временного хранения информации об одном типе изделий

    QRect               Sheet;      // Переменная с размерами листа
    QVector<Stripe>     Products;   // Вектор с информацией об изделиях
    QVector<QRect>      Result;     // Вектор с результатами расчёта
};

#endif // _2DSP_H
