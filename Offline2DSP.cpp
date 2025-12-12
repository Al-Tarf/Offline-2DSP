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

// Предварительно сортируем данные о типах изделий по невозрастанию высоты:
    std::sort(Products.begin(), Products.end(), [] (Stripe a, Stripe b) {return a.qrMeasurements.height() >= b.qrMeasurements.height();} );

// Разворачиваем отсортированный вектор с данными об изделиях и их количестве в вектора просто изделий попутно разбивая изделия на классы согласно алгоритму "Split Fit":
    int iWidth50  =      Sheet.width() / 2,
        iWidth67  = (2 * Sheet.width())/ 3,
        iWidth100 =      Sheet.width();

    for (uint i=0; i < Products.size(); i++)
        for (uint j=0; j<Products[i].uiQuantity; j++) {
            if      (       0 < Products[i].qrMeasurements.width() <= iWidth50)
                buffer.width_0_50.push_back(Products[i].qrMeasurements);     // Будут упакованы в свободные места
            else if (iWidth50 < Products[i].qrMeasurements.width() <= iWidth67)
                buffer.width_51_66.push_back(Products[i].qrMeasurements);    // Будут упакованы во вторую очередь
            else if (iWidth67 < Products[i].qrMeasurements.width() <= iWidth100)
                buffer.width_67_100.push_back(Products[i].qrMeasurements);   // Будут упакованы в первую очередь
            else
                buffer.other.push_back(Products[i].qrMeasurements);          // Либо требуется поворот либо такие прямоугольники не будут упакованы
        }

//-> Тестовый код
    Result << buffer.width_0_50 << buffer.width_51_66 << buffer.width_67_100 << buffer.other;
//<- Тестовый код

// Запускаем перерисовку после расчётов:
    emit signalRepaintResult();
}
