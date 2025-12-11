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
    QVector<QRect>      Buffer;     // Вектор для промежуточного хранения данных
};

#endif // OFFLINE2DSP_H
