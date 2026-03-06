#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "myADC.h"

#define LED_Groen 5
#define LED_Geel 18
#define LED_Rood 19

#define CHANNEL ADC_CHANNEL_0

void app_main(void)
{
    // LED setup
    gpio_reset_pin(LED_Groen);
    gpio_reset_pin(LED_Geel);
    gpio_reset_pin(LED_Rood);

    gpio_set_direction(LED_Groen, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Geel, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Rood, GPIO_MODE_OUTPUT);

    // ADC initialiseren via component
    adc_component_init(CHANNEL);

    while (1)
    {
        int potWaarde = adc_component_read_mv();

        printf("Potentiometer waarde: %d mV\n", potWaarde);

        if (potWaarde < 700)
        {
            gpio_set_level(LED_Groen, 1);
            gpio_set_level(LED_Geel, 0);
            gpio_set_level(LED_Rood, 0);
        }
        else if (potWaarde < 2000)
        {
            gpio_set_level(LED_Groen, 0);
            gpio_set_level(LED_Geel, 1);
            gpio_set_level(LED_Rood, 0);
        }
        else
        {
            gpio_set_level(LED_Groen, 0);
            gpio_set_level(LED_Geel, 0);
            gpio_set_level(LED_Rood, 1);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}