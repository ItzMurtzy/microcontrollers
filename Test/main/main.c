#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "myGPIO.h"

#define builtInLED 22
#define buttonPin 23

int counter = 0;
void app_main(void)
{
    myGPIO_LED_setup(builtInLED);
    myGPIO_BTN_setup(buttonPin);

    while(counter < 5){
        if(myGPIO_BTN_rising_edge(buttonPin)){
            counter++;
            printf("Button pressed %d times\n", counter);
        }
        if(counter >= 5){
            myGPIO_LED_on(builtInLED);
            printf("Counter reached 5, LED turned on\n");
            vTaskDelay(1000); 
            myGPIO_LED_off(builtInLED);
            counter = 0; 
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); 

    }
}
 
