#include <Arduino.h>
#include <gpio.h>
#define LED_PIN D4

void intialise_gpio(int pin_no, int pin_mode)
{
    pinMode(pin_no, pin_mode);
}

void gpio_write(int pin_no, int value)
{
    digitalWrite(pin_no, value);
}