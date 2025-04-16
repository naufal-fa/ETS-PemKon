#ifndef DHT22_H_
#define DHT22_H_

#include "stm32f4xx_hal.h"

void DHT22_Init(GPIO_TypeDef* port, uint16_t pin);
uint8_t DHT22_Read(GPIO_TypeDef* port, uint16_t pin, float *temperature, float *humidity);

#endif /* DHT22_H */