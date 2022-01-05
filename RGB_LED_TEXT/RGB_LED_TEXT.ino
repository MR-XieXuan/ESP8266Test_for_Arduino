
#define RGBLED_R D8
#define RGBLED_G D9
#define RGBLED_B D10


void setup(){
    pinMode(RGBLED_R,OUTPUT);
    pinMode(RGBLED_G,OUTPUT);
    pinMode(RGBLED_B,OUTPUT);
}

void loop(){
    digitalWrite(RGBLED_R,LOW);
    delay(1);
    digitalWrite(RGBLED_G,LOW);
    delay(1);
    digitalWrite(RGBLED_B,LOW);
    delay(1);
    digitalWrite(RGBLED_R,HIGH);
    delay(1);
    digitalWrite(RGBLED_G,HIGH);
    delay(1);
    digitalWrite(RGBLED_B,HIGH);
    delay(1);
}


