#include <SoftwareSerial.h>
SoftwareSerial ESP(10,11); 
const int trigger = 2;
const int echo = 3;
long T;
float distanceCM;
void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  ESP.begin(115200);
}
void loop()
{
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  ESP.print(distanceCM);
  delay(1000);
}