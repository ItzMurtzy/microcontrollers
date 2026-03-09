#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>
#include "sdkconfig.h"
#include "myPWM.h"
#include "driver/adc.h"


#define LED_PIN 5           
#define LEDC_FREQUENCY 1000           

void adc_init()
{
    adc1_config_width(ADC_WIDTH_BIT_12); // 0 - 4095
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); 
}

int read_light()
{
    return adc1_get_raw(ADC1_CHANNEL_6);
}

int map_freq(int adc_value)
{
    
    int min_freq = 100;
    int max_freq = 5000;

    return min_freq + ((max_freq - min_freq) * adc_value) / 4095;
}
void app_main(void)
{  
    pwm_init(LED_PIN, LEDC_FREQUENCY, 0);
    adc_init();
    
    while (1) {
       pwm_set_duty(255);
        int light = adc1_get_raw(ADC1_CHANNEL_6);
        int freq = map_freq(light);
        pwm_set_freq(freq);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}