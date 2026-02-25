#include <stdio.h>
#include "myGPIO.h"
#include "driver/gpio.h"


//  LED
void myGPIO_LED_on(int pin){
    gpio_set_level(pin, 1);
}
void myGPIO_LED_off(int pin){
    gpio_set_level(pin, 0);
}
void myGPIO_LED_toggle(int pin) {
    int level = gpio_get_level(pin);
    gpio_set_level(pin, !level);
}
void myGPIO_LED_setup(int pin)
{
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}
void myGPIO_LED_write_value(int pin){
    int level = gpio_get_level(pin);
    gpio_set_level(pin, level);
}

// Input Knop
int myGPIO_BTN_read(int pin){
    int level = gpio_get_level(pin);
    printf("Button state: %d\n", level);
    return level;
}
void myGPIO_BTN_setup(int pin){
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
}
int myGPIO_BTN_edge(int pin){
    int current_state = gpio_get_level(pin);
    int previous_state = 0; // Assuming the button starts in the unpressed state

    if (current_state != previous_state) {
        previous_state = current_state; // Update previous state
        return current_state; // Return the new state
    }
    return -1; // No change in state
}
int myGPIO_BTN_rising_edge(int pin){
    static int current_state;
    current_state = gpio_get_level(pin);
    static int previous_state = 0; // Assuming the button starts in the unpressed state

    if (current_state == 1 && previous_state == 0) {
        previous_state = current_state; // Update previous state
        return 1; // Rising edge detected
    }
    else{
         previous_state = current_state; // Update previous state
    return 0; // No rising edge detected
    }
   
}
int myGPIO_BTN_falling_edge(int pin){
    int current_state = gpio_get_level(pin);
    int previous_state = 1; // Assuming the button starts in the pressed state

    if (current_state == 0 && previous_state == 1) {
        previous_state = current_state; // Update previous state
        return 1; // Falling edge detected
    }
    else
    {
         previous_state = current_state; // Update previous state
    return 0; // No falling edge detected
    }
   
}
