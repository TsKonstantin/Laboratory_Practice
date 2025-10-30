#include <stdint.h>
#include "init.h"

#define LED1_PIN    0
#define LED2_PIN    7
#define LED3_PIN    14
#define BTN_NEXT    13 // PC13
#define BTN_FREQ    7  // PD7
#define BTN_SELECT  5  // PD5

#define READ_BTN_NEXT   ((GPIOC->IDR >> BTN_NEXT) & 1)
#define READ_BTN_FREQ   ((GPIOD->IDR >> BTN_FREQ) & 1)
#define READ_BTN_SELECT ((GPIOD->IDR >> BTN_SELECT) & 1)

#define LED_ON(pin)     (GPIOB->BSRR = (1U << (pin)))
#define LED_OFF(pin)    (GPIOB->BSRR = (1U << ((pin) + 16)))
#define LED_TOGGLE(pin) (GPIOB->ODR ^= (1U << (pin)))

static void delay_loop(volatile uint32_t count) { while(count--) __NOP(); }
static void delay_ms(uint32_t ms) { for(uint32_t i=0;i<ms;i++) delay_loop(3800); } 

#define FREQ_COUNT 3

GPIO_PB0_INIT();

int main(void) {
    // Тактирование портов
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

    // Настройка выходов
    GPIOB->MODER &= ~((3U<<(LED1_PIN*2)) | (3U<<(LED2_PIN*2)) | (3U<<(LED3_PIN*2)));
    GPIOB->MODER |=  ((1U<<(LED1_PIN*2)) | (1U<<(LED2_PIN*2)) | (1U<<(LED3_PIN*2)));

    // Настройка кнопок
    GPIOC->MODER &= ~(3U << (BTN_NEXT*2));  GPIOC->PUPDR &= ~(3U << (BTN_NEXT*2));
    GPIOD->MODER &= ~((3U << (BTN_FREQ*2)) | (3U << (BTN_SELECT*2)));
    GPIOD->PUPDR &= ~((3U << (BTN_FREQ*2)) | (3U << (BTN_SELECT*2)));
    GPIOD->PUPDR |= ((1U << (BTN_FREQ*2)) | (1U << (BTN_SELECT*2))); // pull-up

    uint8_t prev_next=0, prev_freq=0, prev_select=0;
    uint8_t led_enabled[3]={0,0,0};   // включение диодов
    uint8_t led_blink[3]={0,0,0};     // режим мигания
    uint8_t led_freq[3]={0,0,0};      // индекс частоты для каждого диода
    uint32_t led_timer[3]={0,0,0};    // таймер для каждого диода
    uint8_t select_led=0;              // выбранный диод

    const uint8_t leds[]={LED1_PIN, LED2_PIN, LED3_PIN};

    // отдельные массивы частот для каждого диода
    const uint32_t freq_delay[3][FREQ_COUNT] = {
        {70, 250, 500},   // PB0
        {90, 350, 600},   // PB7
        {120, 400, 700}   // PB14
    };

    while(1) {
        // PC13: включаем следующий диод или сбрасываем все
        if(READ_BTN_NEXT==0){
            delay_loop(550);
            if(READ_BTN_NEXT==0 && prev_next==0){
                // проверяем, все ли диоды уже включены
                uint8_t all_on = 1;
                for(uint8_t i=0;i<3;i++) if(!led_enabled[i]) all_on=0;

                if(all_on){
                    // если все включены, гасим все
                    for(uint8_t i=0;i<3;i++){
                        led_enabled[i]=0;
                        LED_OFF(leds[i]);
                    }
                } else {
                    // включаем первый выключенный диод
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

        // PD5: выбор диода для настройки
        if(READ_BTN_SELECT==0){
            delay_loop(550);
            if(READ_BTN_SELECT==0 && prev_select==0){
                select_led++;
                if(select_led>2) select_led=0;
                prev_select=1;
            }
        } else prev_select=0;

        // PD7: включение/выключение мигания и смена частоты для выбранного диода
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

        delay_ms(1);
    }
}
