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

#define GPIOG_MODER_PIN9_ON       0x40000   // MODER9 = 01
#define GPIOG_OTYPER_PIN9_PP      0x0000    // Push-Pull
#define GPIOG_OSPEEDR_PIN9_MID    0x40000   // OSPEEDR9 = 01
#define GPIOG_PUPDR_PIN9_NOPUPD   0x0000    // No pull-up/pull-down

// === Инициализация дополнительных светодиодов === 
void GPIO_PF11_INIT(void); // Настройка светодиода PF11 прямым обращением к регистрам
void GPIO_PG9_INIT(void); // Настройка светодиода PG9 собственными макросами

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
    uint8_t *PB0_mode, uint8_t *PB7_mode,uint8_t *PB14_mode,
    uint8_t *PD3_mode, uint8_t *PD5_mode, uint8_t *PE10_mode, 
);

#endif // INIT_H