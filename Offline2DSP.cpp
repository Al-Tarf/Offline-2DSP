#include "Offline2DSP.h"

// Конструктор:
Offline2DSP::Offline2DSP(QObject *parent, uint uiWidth, uint uiHeight)
    : QObject(parent), Sheet(0, 0, uiWidth, uiHeight) {
// На всякий случай очищаем вектора с исходными данными:
    Products.clear();
    Result.clear();
}

// Деструктор:
Offline2DSP::~Offline2DSP(){

}

// Слот производящий расчёты:
void Offline2DSP::slotRunCalculate() {
// Перерисовываем лист-заготовку на экране если есть данные о его размере:
    emit signalRepaintResult();
// Проверяем все ли данные получены, если нет завершаем выполнение слота:
/* (корректность данных в Products проверяется при сборе данных из таблицы в методе ProductsDialog::CheckCellData) */
    if (!Sheet.width() || !Sheet.height() || !Products.size()) return;

// Разворачиваем вектор с данными об изделиях и их количестве в вектор просто изделий:
    for (uint i=0; i < Products.size(); i++)
        for (uint j=0; j<Products[i].uiQuantity; j++) Buffer.push_back(Products[i].qrMeasurements);

//-> Тестовый код
    Result = Buffer;
//<- Тестовый код

// Запускаем перерисовку после расчётов:
    emit signalRepaintResult();
}
