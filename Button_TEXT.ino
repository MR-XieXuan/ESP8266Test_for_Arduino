//Text 
#include <Wire.h>

#define BUTTON  0
#define MOM     2

void setup(){
    Serial.begin(9600);
    pinMode(BUTTON,INPUT_PULLUP);
    pinMode(MOM,OUTPUT);
}

void loop(){
  if(digitalRead(BUTTON)==LOW){
    Serial.print("0\n");
    digitalWrite(MOM,LOW);
  }else if(digitalRead(BUTTON)==HIGH ){
    Serial.print("1\n");
    digitalWrite(MOM,HIGH);
  }
}

