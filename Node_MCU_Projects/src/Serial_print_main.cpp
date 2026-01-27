#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Hello from ESP8266");
}

void loop() {
  Serial.println("Alive");
  delay(1000);
}
