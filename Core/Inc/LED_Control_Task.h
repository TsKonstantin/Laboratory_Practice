#ifndef LED_CONTROL_TASK_H
#define LED_CONTROL_TASK_H

#include "stm32f4xx.h"
#include <stdint.h>

#define LED1_PIN    0
#define LED2_PIN    7
#define LED3_PIN    14

#define BTN_NEXT    13  // PC13
#define BTN_FREQ    7   // PD7
#define BTN_SELECT  5   // PD5

#define READ_BTN_NEXT   ((GPIOC->IDR >> BTN_NEXT) & 1)
#define READ_BTN_FREQ   ((GPIOD->IDR >> BTN_FREQ) & 1)
#define READ_BTN_SELECT ((GPIOD->IDR >> BTN_SELECT) & 1)

#define LED_ON(pin)     (GPIOB->BSRR = (1U << (pin)))
#define LED_OFF(pin)    (GPIOB->BSRR = (1U << ((pin) + 16)))
#define LED_TOGGLE(pin) (GPIOB->ODR ^= (1U << (pin)))

void LED_Control_Task_Init(void);
void LED_Control_Task(void);

#endif 
