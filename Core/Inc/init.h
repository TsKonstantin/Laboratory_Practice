#include <stdint.h>
#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"
// #include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"

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

void GPIO_PB0_INIT(void);
void GPIO_PB7_INIT(void);
void GPIO_PB14_INIT(void);  