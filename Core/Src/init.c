#include "init.h"

// === Настройка дополнительных светодиодов ===
void GPIO_PF11_INIT(void) // Настройка светодиода PF11
{
    *(uint32_t*)(0x40021400UL + 0x00UL) |= 0x400000; // MODER11 = 01
    *(uint32_t*)(0x40021400UL + 0x04UL) |= 0x00000000; // OTYPER11 = 00
    *(uint32_t*)(0x40021400UL + 0x08UL) |= 0x400000; // OSPEEDR11 = 01
    *(uint32_t*)(0x40021400UL + 0x0CUL) |= 0x00000000; // PUPDR11 = 00
}

void GPIO_PG9_INIT(void) // Настройка светодиода PG9
{
    GPIOG_MODER |= GPIOG_MODER_PIN9_ON;
    GPIOG_OTYPER |= GPIOG_OTYPER_PIN9_PP;
    GPIOG_OSPEEDR |= GPIOG_OSPEEDR_PIN9_MID;
    GPIOG_PUPDR |= GPIOG_PUPDR_PIN9_NOPUPD;
}

// === Тактирование портов ===
void GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN;
}

void GPIO_PB0_INIT(void) // Настройка жёлтого светодиода PB0
{
    GPIOB->MODER |= GPIO_MODER_MODER0_0; // MODER14 = 01 (выход)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_0;  // OTYPER14 = 0 (push-pull) 
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_0; // Medium speed
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0;  // No pull
}

void GPIO_PB7_INIT(void) // Настройка синего светодиода PB7
{
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x4000; // MODER7 - 01
    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00000000; // OTYPER - 00
    *(uint32_t*)(0x40020400UL + 0x08UL) |= 0x4000; // OSPEEDR7 - 01
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= 0x00000000; // PUPDR7 - 00 
}

void GPIO_PB14_INIT(void) // Настройка красного светодиода PB14
{
    GPIOB_MODER |= GPIOB_MODER_PIN14_ON;
    GPIOB_OTYPER |= GPIOB_OTYPER_PIN14_PP;
    GPIOB_OSPEEDR |= GPIOB_OSPEEDR_PIN14_MID;  
    GPIOB_PUPDR |= GPIOB_PUPDR_PIN14_NOPUPD;
}

// Настройка кнопки PD3 
void Button_PD3_Init(void)
{
    GPIOD->MODER &= ~GPIO_MODER_MODER3;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD3;
    GPIOD->PUPDR |=  GPIO_PUPDR_PUPD3_0; // подтяжка вверх
}

// Настройка кнопки PD5 
void Button_PD5_Init(void)
{
    GPIOD->MODER &= ~GPIO_MODER_MODER5;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD5;
    GPIOD->PUPDR |=  GPIO_PUPDR_PUPD5_0; // подтяжка вверх
}

// Настройка кнопки PE10 
void Button_PE10_Init(void)
{
    GPIOE->MODER &= ~GPIO_MODER_MODER10;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD10;
    GPIOE->PUPDR |=  GPIO_PUPDR_PUPD10_0; // подтяжка вверх
}

// Отладка (чтение MODER выводов)
void Debug_Read_MODER(
    uint8_t *PB0_mode, uint8_t *PB7_mode, uint8_t *PB14_mode,
    uint8_t *PD3_mode, uint8_t *PD5_mode, uint8_t *PE10_mode)
{
    uint32_t moderB = GPIOB->MODER;
    uint32_t moderD = GPIOD->MODER;
    uint32_t moderE = GPIOE->MODER;
    
    *PB0_mode  = (moderB >> 0)  & 0x3;
    *PB7_mode  = (moderB >> 14) & 0x3;
    *PB14_mode = (moderB >> 28) & 0x3;
    *PD3_mode  = (moderD >> 6)  & 0x3;
    *PD5_mode  = (moderD >> 10) & 0x3;
    *PE10_mode = (moderE >> 20) & 0x3;
}