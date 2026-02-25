//  LED
void myGPIO_LED_on(int pin);
void myGPIO_LED_off(int pin);
void myGPIO_LED_toggle(int pin);
void myGPIO_LED_setup(int pin);
void myGPIO_LED_write_value(int pin);

// Input Knop
int myGPIO_BTN_read(int pin);
void myGPIO_BTN_setup(int pin);
int myGPIO_BTN_edge(int pin);
int myGPIO_BTN_rising_edge(int pin);
int myGPIO_BTN_falling_edge(int pin);
