#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "myGpio.h"
#include "esp_attr.h"

#define KNOP_PIN 26
#define LED_PIN 27

//static void IRAM_ATTR KNOP_ISR(void* args)
//{
//    myGPIO_LED_Toggle(LED_PIN);
//}

void app_main(void)
{
    myGPIO_KNOP_Setup(KNOP_PIN);
    myGPIO_KNOP_SetupInterrupt(KNOP_PIN);

    //gpio_set_intr_type(KNOP_PIN, GPIO_INTR_NEGEDGE);
    //gpio_install_isr_service(0);
    //gpio_isr_handler_add(KNOP_PIN, KNOP_ISR, 0);

    myGPIO_LED_Setup(LED_PIN);

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
    
}



