#include <Arduino.h>

void setup()
{
	// 设置通信频率为9600
	Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
}

void loop()
{
  if (digitalRead(7) == HIGH)
  {
    digitalWrite(2, 1);
    delay(200);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    delay(200); 
    digitalWrite(3, 0);
    digitalWrite(4, 1);  
    delay(200);
    digitalWrite(4, 0);
    digitalWrite(2, 1);
  }
  else
  {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 0);
  }
}
