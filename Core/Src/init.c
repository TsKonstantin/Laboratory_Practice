#include "init.h"

void GPIO_PB0_INIT(void) // Настройка жёлтого светодиода PB0
{
    GPIOB->MODER |= GPIO_MODER_MODER0_0; // MODER14 = 01 (выход)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_0;  // OTYPER14 = 0 (push-pull) 
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_0; // Medium speed
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0;  // No pull
}

void GPIO_PB7_INIT(void)
{
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x4000; // MODER7 - 01
    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00000000; // OTYPER - 00
    *(uint32_t*)(0x40020400UL + 0x08UL) |= 0x4000; // OSPEEDR7 - 01
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= 0x00000000; // PUPDR7 - 00 
}

void GPIO_PB14_INIT(void) // Настройка светодиода PB14
{
    GPIOB_MODER |= GPIOB_MODER_PIN14_ON;
    GPIOB_OTYPER |= GPIOB_OTYPER_PIN14_PP;
    GPIOB_OSPEEDR |= GPIOB_OSPEEDR_PIN14_MID;  
    GPIOB_PUPDR |= GPIOB_PUPDR_PIN14_NOPUPD;
}