#include "init.h"

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

// === Настройка кнопки PD3 ===
void Button_PD3_Init(void)
{
    GPIOD->MODER &= ~GPIO_MODER_MODER3;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD3;
    GPIOD->PUPDR |=  GPIO_PUPDR_PUPD3_0; // подтяжка вверх
}

// === Настройка кнопки PD5 ===
void Button_PD5_Init(void)
{
    GPIOD->MODER &= ~GPIO_MODER_MODER5;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD5;
    GPIOD->PUPDR |=  GPIO_PUPDR_PUPD5_0; // подтяжка вверх
}

// === Настройка кнопки PE10 ===
void Button_PE10_Init(void)
{
    GPIOE->MODER &= ~GPIO_MODER_MODER10;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD10;
    GPIOE->PUPDR |=  GPIO_PUPDR_PUPD10_0; // подтяжка вверх
}

// === Отладка (чтение MODER выводов) ===
void Debug_Read_MODER(
    uint8_t *PE0_mode,  uint8_t *PE1_mode,  uint8_t *PE2_mode,  uint8_t *PE3_mode,  uint8_t *PD3_mode,
    uint8_t *PE4_mode,  uint8_t *PE5_mode,  uint8_t *PD5_mode,  uint8_t *PE6_mode,  uint8_t *PE7_mode,
    uint8_t *PE8_mode,  uint8_t *PE9_mode,  uint8_t *PE10_mode, uint8_t *PE11_mode,
    uint8_t *PE12_mode, uint8_t *PE13_mode, uint8_t *PE14_mode, uint8_t *PE15_mode)
{
    uint32_t moderD = GPIOD->MODER;
    uint32_t moderE = GPIOE->MODER;

    *PE0_mode  = (moderE >> 0)  & 0x3;
    *PE1_mode  = (moderE >> 2)  & 0x3;
    *PE2_mode  = (moderE >> 4)  & 0x3;
    *PD3_mode  = (moderD >> 6)  & 0x3;
    *PE3_mode  = (moderE >> 6)  & 0x3;
    *PE4_mode  = (moderE >> 8)  & 0x3;
    *PD5_mode  = (moderD >> 10) & 0x3;
    *PE5_mode  = (moderE >> 10) & 0x3;
    *PE6_mode  = (moderE >> 12) & 0x3;
    *PE7_mode  = (moderE >> 14) & 0x3;
    *PE8_mode  = (moderE >> 16) & 0x3;
    *PE9_mode  = (moderE >> 18) & 0x3;
    *PE10_mode = (moderE >> 20) & 0x3;
    *PE11_mode = (moderE >> 22) & 0x3;
    *PE12_mode = (moderE >> 24) & 0x3;
    *PE13_mode = (moderE >> 26) & 0x3;
    *PE14_mode = (moderE >> 28) & 0x3;
    *PE15_mode = (moderE >> 30) & 0x3;
}