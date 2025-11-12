#include "init.h"
#include <stdint.h>
#include "LED_Control_Task.h" // Задание на защиту

// --- Переменные состояния MODER для каждого пина порта E ---
uint8_t PB0_mode,  PB7_mode,  PB14_mode,
uint8_t PD3_mode;  PD5_mode,  PE10_mode;

int main(void)
{
    /*
    === Задание на защиту ===
    GPIO_Init();
    LED_Control_Task_Init();
    */

    // === Инициализация тактирования ===
    GPIO_Clock_Init();

    // === Инициализация светодиодов-индикаторов ===
    Button_PD3_Init();
    Button_PD5_Init();
    Button_PE10_Init();

    // === Инициализация светодиодов-индикаторов ===
    LED_PB0_Init();
    LED_PB7_Init();
    LED_PB14_Init();

    /*
    // === Инициализация дополнительных светодиодов ===
    void GPIO_PF11_INIT(void); // Настройка светодиода PF11 прямым обращением к регистрам
    void GPIO_PG9_INIT(void); // Настройка светодиода PG9 собственными макросами
    */

    // === Изначально все светодиоды выключены ===
    GPIOB->BSRR = GPIO_BSRR_BR_0 | GPIO_BSRR_BR_7 | GPIO_BSRR_BR_14;
    GPIOE->BSRR = GPIO_BSRR_BR_10;

    while (1)
    {
        /*  
        // --- Задание на защиту ---
        LED_Control_Task();
        */

        // --- Кнопка PD3: устанавливает GPIOE во вход ---
        if (!(GPIOD->IDR & GPIO_IDR_ID3))
        {
            GPIOE->MODER &= ~0x55555555;     // весь порт E — вход
            GPIOB->BSRR = GPIO_BSRR_BS_14;   // красный светодиод - индикатор PB14 ВКЛ
        }
        else
        {
            GPIOB->BSRR = GPIO_BSRR_BR_14;   // красный светодиод - индикатор PB14 ВЫКЛ
        }

        // --- Кнопка PD5: устанавливает GPIOE в выход ---
        if (!(GPIOD->IDR & GPIO_IDR_ID5))
        {
            GPIOE->MODER = 0x55555555;       // весь порт E — выход
            GPIOB->BSRR = GPIO_BSRR_BS_7;    // синий светодиод - индикатор PB7 ВКЛ
        }
        else
        {
            GPIOB->BSRR = GPIO_BSRR_BR_7;    // синий светодиод - индикатор PB7 ВКЛ
        }

        // --- Кнопка PE10: управление по режиму ---
        if (GPIOE->MODER == 0x00000000) // порт E — вход
        {
            if (!(GPIOE->IDR & GPIO_IDR_ID10))
                GPIOB->BSRR = GPIO_BSRR_BS_0; // жёлтый светодиод - индикатор PD0 ВКЛ
            else
                GPIOB->BSRR = GPIO_BSRR_BR_0; // жёлтый светодиод - индикатор PD 0 ВЫКЛ
        }
        else if (GPIOE->MODER == 0x55555555) // порт E — выход
        {
            if (!(GPIOE->IDR & GPIO_IDR_ID10))
                GPIOE->BSRR = GPIO_BSRR_BS_10; // PE10 светодиод ВКЛ
            else
                GPIOE->BSRR = GPIO_BSRR_BR_10; // PE10 светодиод ВЫКЛ
        }

        // --- Отладка состояний ---
        Debug_Read_MODER(
            &PB0_mode, &PB7_mode, &PB14_mode, &PD3_mode,
            &PD3_mode, &PD5_mode, &PE10_mode, 
        );
    }
} 