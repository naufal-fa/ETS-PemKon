#include "dht22.h"

static void DHT22_SetPinOutput(GPIO_TypeDef* port, uint16_t pin);
static void DHT22_SetPinInput(GPIO_TypeDef* port, uint16_t pin);
static void DHT22_DelayMicroseconds(uint32_t us);

void DHT22_Init(GPIO_TypeDef* port, uint16_t pin) {
    DHT22_SetPinOutput(port, pin);
}

uint8_t DHT22_Read(GPIO_TypeDef* port, uint16_t pin, float *temperature, float *humidity) {
    uint8_t data[5] = {0};
    uint8_t i, j;

    /* Start signal */
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    DHT22_DelayMicroseconds(20);

    /* Set pin as input */
    DHT22_SetPinInput(port, pin);

    /* Wait for DHT22 response */
    while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET);
    while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET);

    /* Read 40 bits of data */
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET);
            DHT22_DelayMicroseconds(30);
            if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) {
                data[j] |= (1 << (7 - i));
            }
            while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET);
        }
    }

    /* Convert data to temperature and humidity */
    *humidity = (float)data[0] + (float)data[1] / 256.0f;
    *temperature = (float)data[2] + (float)data[3] / 256.0f;

    return (data[4] == (data[0] + data[1] + data[2] + data[3])); /* Check checksum */
}

static void DHT22_SetPinOutput(GPIO_TypeDef* port, uint16_t pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

static void DHT22_SetPinInput(GPIO_TypeDef* port, uint16_t pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

static void DHT22_DelayMicroseconds(uint32_t us) {
    /* Implementasi delay mikrodetik menggunakan HAL_Delay */
    uint32_t start = HAL_GetTick();
    while ((HAL_GetTick() - start) < (us / 1000)); // Mengonversi mikrodetik ke milidetik
}