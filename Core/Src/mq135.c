#include "mq135.h"

float MQ135_Read(ADC_HandleTypeDef* hadc) {
    uint32_t adcValue = 0;
    float voltage = 0.0f;
    float concentration = 0.0f;

    // Mulai konversi ADC
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    adcValue = HAL_ADC_GetValue(hadc);
    HAL_ADC_Stop(hadc);

    // Menghitung tegangan dari nilai ADC
    voltage = (adcValue * 3.3f) / 4095.0f; // Misalkan Vref = 3.3V

    // Menghitung konsentrasi gas (misalnya, CO2) berdasarkan tegangan
    // Anda perlu menyesuaikan rumus ini berdasarkan karakteristik sensor MQ135
    concentration = voltage * 100; // Contoh konversi, sesuaikan dengan datasheet

    return concentration;
}