#ifndef gpio_h
#define gpio_h
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#define LED_PIN D4   // Built-in LED (active LOW)
void intialise_gpio(int pin_no, int pin_mode);
void gpio_write(int pin_no, int value);
#ifdef __cplusplus
}
#endif
#endif