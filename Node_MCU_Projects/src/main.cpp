#include <Arduino.h>

extern "C" {
  #include <wifi_mgr.h>
#include <gpio.h>
}

#define LED_PIN D4   // Built-in LED (active LOW)



void setup()
{
    Serial.begin(115200);
    delay(500);

    intialise_gpio(LED_PIN, OUTPUT);

    Serial.println("\n--- ESP8266 WiFi Demo ---");

    wifi_init();
}

void loop()
{
    wifi_run();
}
