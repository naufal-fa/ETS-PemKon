#ifndef RELAY_H_
#define RELAY_H_

#include "stm32f4xx_hal.h"

void Relay_Init(GPIO_TypeDef* port, uint16_t pin);
void Relay_On(GPIO_TypeDef* port, uint16_t pin);
void Relay_Off(GPIO_TypeDef* port, uint16_t pin);
void Relay_Toggle(GPIO_TypeDef* port, uint16_t pin);

#endif /* RELAY_H */