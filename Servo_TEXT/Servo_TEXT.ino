#include <Servo.h>

Servo myservo;
int a = 0;

int i = 0;

void setup()
{
    // put your setup code here, to run once:
    myservo.attach(D4);
    Serial.begin(9600);
    pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (digitalRead(D1) == 0)
    {
        if(i > 0){
           i--; 
        }
        delay(10);
        Serial.printf("%d", i);
        myservo.write(i);
    }
    else if(digitalRead(D2)==0)
    {
        if(i <180 ){
            i++;
        }
        delay(10);
        Serial.printf("%d", i);
        myservo.write(i);
    }
}
