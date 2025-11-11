#ifndef INIT_H
#define INIT_H

#include "stm32f4xx.h"
#include <stdint.h>
#define RCC_GPIOA             *(uint32_t*)(0x40023800UL + 0x30UL) 
#define RCC_GPIOB             *(uint32_t*)(0x40023800UL + 0x30UL) 

#define GPIOB_MODER           *(uint32_t*)(0x40020400UL+0x00UL) 
#define GPIOB_OTYPER          *(uint32_t*)(0x40020400UL+0x04UL) 
#define GPIOB_OSPEEDR         *(uint32_t*)(0x40020400UL+0x08UL) 
#define GPIOB_PUPDR           *(uint32_t*)(0x40020400UL+0x0CUL)
#define GPIOB_ODR             *(uint32_t*)(0x40020400UL+0x14UL)

#define RCC_GPIOA_EN_ON         0x01
#define RCC_GPIOB_EN_ON         0x02
#define GPIOB_MODER_PIN14_ON     0x10000000
#define GPIOB_OTYPER_PIN14_PP    0x00000000
#define GPIOB_OSPEEDR_PIN14_MID  0x10000000
#define GPIOB_PUPDR_PIN14_NOPUPD 0x00000000
#define GPIOB_ODR_PIN14_ON       0x00000001

// === Тактирование ===
void GPIO_Clock_Init(void);

// === Кнопки ===
void Button_PD3_Init(void);
void Button_PD5_Init(void);
void Button_PE10_Init(void);

// === Светодиоды ===
void LED_PB0_Init(void);
void LED_PB7_Init(void);
void LED_PB14_Init(void);

// === Отладка ===
void Debug_Read_MODER(
    uint8_t *PE0_mode,  uint8_t *PE1_mode,  uint8_t *PE2_mode,  uint8_t *PE3_mode,  uint8_t *PD3_mode,
    uint8_t *PE4_mode,  uint8_t *PE5_mode,  uint8_t *PD5_mode,  uint8_t *PE6_mode,  uint8_t *PE7_mode,
    uint8_t *PE8_mode,  uint8_t *PE9_mode,  uint8_t *PE10_mode, uint8_t *PE11_mode,
    uint8_t *PE12_mode, uint8_t *PE13_mode, uint8_t *PE14_mode, uint8_t *PE15_mode
);

#endif // INIT_H