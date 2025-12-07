#include "_2DSP.h"

// Конструктор:
_2DSP::_2DSP(QObject *parent, uint uiLenghth, uint uiWidth)
    : QObject(parent), Sheet(0, 0, uiLenghth, uiWidth) {
// На всякий случай очищаем вектора с исходными данными:
    Products.clear();
    Result.clear();
}

// Деструктор:
_2DSP::~_2DSP(){

}

// Слот производящий расчёты:
void _2DSP::slotRunCalculate() {
// Выходим если не все данные получены:

// Запускаем перерисовку после расчётов:
    emit signalRepaintResult();
}
