#include "led_control_task.h"

#define FREQ_COUNT 3

static void delay_loop(volatile uint32_t count) { while(count--) __NOP(); }
static void delay_ms(uint32_t ms) { for(uint32_t i=0;i<ms;i++) delay_loop(3800); } 

// === Переменные состояния кнопок и светодиодов ===
static uint8_t prev_next=0, prev_freq=0, prev_select=0;
static uint8_t led_enabled[3]={0,0,0};
static uint8_t led_blink[3]={0,0,0};
static uint8_t led_freq[3]={0,0,0};
static uint32_t led_timer[3]={0,0,0};
static uint8_t select_led=0;

static const uint8_t leds[]={LED1_PIN, LED2_PIN, LED3_PIN};

// === Диапазон частот для каждого диода ===
static const uint32_t freq_delay[3][FREQ_COUNT] = {
    {70, 250, 500},   // PB0
    {90, 350, 600},   // PB7
    {120, 400, 700}   // PB14
};

// === Инициализация ===
void LED_Control_Task_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

    // Настройка выходов (PB0, PB7, PB14)
    GPIOB->MODER &= ~((3U<<(LED1_PIN*2)) | (3U<<(LED2_PIN*2)) | (3U<<(LED3_PIN*2)));
    GPIOB->MODER |=  ((1U<<(LED1_PIN*2)) | (1U<<(LED2_PIN*2)) | (1U<<(LED3_PIN*2)));

    // Настройка кнопок
    GPIOC->MODER &= ~(3U << (BTN_NEXT*2));  
    GPIOC->PUPDR &= ~(3U << (BTN_NEXT*2));
    GPIOD->MODER &= ~((3U << (BTN_FREQ*2)) | (3U << (BTN_SELECT*2)));
    GPIOD->PUPDR &= ~((3U << (BTN_FREQ*2)) | (3U << (BTN_SELECT*2)));
    GPIOD->PUPDR |= ((1U << (BTN_FREQ*2)) | (1U << (BTN_SELECT*2))); // pull-up
}

// Управление диапазонами частот ===
void LED_Control_Task(void) {
    // Кнопка PC13 - зажигание светодиодов поочерёдно
    if(READ_BTN_NEXT==0){
        delay_loop(550);
        if(READ_BTN_NEXT==0 && prev_next==0){
            uint8_t all_on = 1;
            for(uint8_t i=0;i<3;i++) if(!led_enabled[i]) all_on=0;

            if(all_on){
                for(uint8_t i=0;i<3;i++){
                    led_enabled[i]=0;
                    LED_OFF(leds[i]);
                }
            } else {
                for(uint8_t i=0;i<3;i++){
                    if(!led_enabled[i]){
                        led_enabled[i]=1;
                        LED_ON(leds[i]);
                        break;
                    }
                }
            }
            prev_next=1;
        }
    } else prev_next=0;

    // Кнопка PD5 - выбрать диод для настройки диапазона частот
    if(READ_BTN_SELECT==0){
        delay_loop(550);
        if(READ_BTN_SELECT==0 && prev_select==0){
            select_led++;
            if(select_led>2) select_led=0;
            prev_select=1;
        }
    } else prev_select=0;

    // Кнопка PD7 - переключать частоты в светодиода
    if(READ_BTN_FREQ==0){
        delay_loop(550);
        if(READ_BTN_FREQ==0 && prev_freq==0){
            led_blink[select_led] = !led_blink[select_led];
            led_freq[select_led]++;
            if(led_freq[select_led]>=FREQ_COUNT) led_freq[select_led]=0;
            prev_freq=1;
        }
    } else prev_freq=0;

    // Обновление диодов
    for(uint8_t i=0;i<3;i++){
        if(!led_enabled[i]){
            LED_OFF(leds[i]);
            led_timer[i]=0;
            continue;
        }
        if(led_blink[i]){
            led_timer[i]++;
            if(led_timer[i]>=freq_delay[i][led_freq[i]]){
                LED_TOGGLE(leds[i]);
                led_timer[i]=0;
            }
        } else {
            LED_ON(leds[i]);
            led_timer[i]=0;
        }
    }
}
