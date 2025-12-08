#include "Offline2DSP.h"

// Конструктор:
Offline2DSP::Offline2DSP(QObject *parent, uint uiLenghth, uint uiWidth)
    : QObject(parent), Sheet(0, 0, uiLenghth, uiWidth) {
// На всякий случай очищаем вектора с исходными данными:
    Products.clear();
    Result.clear();
}

// Деструктор:
Offline2DSP::~Offline2DSP(){

}

// Слот производящий расчёты:
void Offline2DSP::slotRunCalculate() {
// Выходим если не все данные получены:

// Запускаем перерисовку после расчётов:
    emit signalRepaintResult();
}
