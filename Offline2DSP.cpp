#include "Offline2DSP.h"

// Конструктор:
Offline2DSP::Offline2DSP(QObject *parent, uint uiLength, uint uiWidth)
    : QObject(parent), Sheet(0, 0, uiLength, uiWidth) {
// На всякий случай очищаем вектора с исходными данными:
    Products.clear();
    Result.clear();
}

// Деструктор:
Offline2DSP::~Offline2DSP(){

}

// Слот производящий расчёты:
void Offline2DSP::slotRunCalculate() {
// Проверяем все ли данные получены:
/* (корректность данных в Products проверяется при сборе данных из таблицы в методе ProductsDialog::CheckCellData) */
    if (!Sheet.width() || !Sheet.height() || !Products.size()) return;

// Запускаем перерисовку после расчётов:
        emit signalRepaintResult();
}
