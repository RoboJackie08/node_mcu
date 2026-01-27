// #include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }

#include <Arduino.h>

void setup() {
  pinMode(D4, OUTPUT);   // Safe pin
}

void loop() {
  digitalWrite(D4, LOW);
  delay(500);
  digitalWrite(D4, HIGH);
  delay(500);
}
