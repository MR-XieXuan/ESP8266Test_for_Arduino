//Text 
#include <Wire.h>

#define LED  D2

void setup(){
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
}

void loop(){
    Serial.print("0\n");
    digitalWrite(LED,LOW);
    delay(1000);
    Serial.print("1\n");
    digitalWrite(LED,HIGH);
    delay(1000);
}

