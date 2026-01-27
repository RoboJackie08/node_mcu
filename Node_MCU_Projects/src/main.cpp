#include <Arduino.h>

extern "C" {
  #include "wifi_mgr.h"
}

#define LED_PIN D4   // Built-in LED (active LOW)

unsigned long last_print = 0;

void setup()
{
    Serial.begin(115200);
    delay(500);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // LED OFF

    Serial.println("\n--- ESP8266 WiFi Template ---");

    wifi_init();
}

void loop()
{
    wifi_loop();

    /* Status indication */
    if (wifi_is_connected())
        digitalWrite(LED_PIN, LOW);   // LED ON
    else
        digitalWrite(LED_PIN, HIGH);  // LED OFF

    /* Periodic logging */
    if (millis() - last_print > 2000)
    {
        last_print = millis();

        if (wifi_is_connected())
        {
            Serial.print("[WiFi] RSSI: ");
            Serial.print(wifi_get_rssi());
            Serial.println(" dBm");
        }
        else
        {
            Serial.println("[WiFi] Not connected");
        }
    }
}
