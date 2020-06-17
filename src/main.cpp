#include <Arduino.h>

void setup() {

  Serial.begin(9600);
}


int val = 0;

void loop() {

  val = analogRead(1);

  Serial.println(val);
  delay(500); 
}