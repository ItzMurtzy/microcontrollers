#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "myADC.h"
#include "myGPIO.h"

#define POT_CHANNEL ADC_CHANNEL_0
#define BUTTON_PIN 0
#define LED_PIN 2

#define CODE_LENGTH 4

int correct_code[CODE_LENGTH] = {1,2,3,4};
int entered_code[CODE_LENGTH];

int digit_index = 0;

int getDigitFromPot()
{
    int adc = myADC_getValue(POT_CHANNEL);

    // ADC range 0-4095 -> 0-9
    int digit = (adc * 10) / 4096;

    if(digit > 9)
        digit = 9;

    return digit;
}

void checkCode()
{
    int correct = 1;

    for(int i = 0; i < CODE_LENGTH; i++)
    {
        if(entered_code[i] != correct_code[i])
        {
            correct = 0;
        }
    }

    if(correct)
    {
        printf("Unlocked!\n");
        myGPIO_LED_On(LED_PIN);
        vTaskDelay(pdMS_TO_TICKS(3000));
        myGPIO_LED_Off(LED_PIN);
    }
    else
    {
        printf("Wrong code\n");
    }
}

void app_main(void)
{

    myADC_setup(POT_CHANNEL);

    myGPIO_LED_Setup(LED_PIN);
    myGPIO_KNOP_Setup(BUTTON_PIN);

    printf("Enter 4 digit code\n");

    while(1)
    {
        int digit = getDigitFromPot();

        printf("\rSelected digit: %d", digit);
        fflush(stdout);

        if(myGPIO_KNOP_GetFlank(BUTTON_PIN))
        {
            entered_code[digit_index] = digit;

            printf("\nDigit %d = %d\n", digit_index+1, digit);

            digit_index++;

            if(digit_index >= CODE_LENGTH)
            {
                checkCode();
                digit_index = 0;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}