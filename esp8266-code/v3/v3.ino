#include "ThingSpeak.h"
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <AccelStepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 5    //D1
#define IN2 4    //D2
#define IN3 14   //D5
#define IN4 12   //D6

// initialize the stepper library
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "realmeX2"; //SSID
char pass[] = "123456798"; // Password
//--------------------------------------- ----//

const int trigger = D7;
const int echo = D8;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField = 1884400; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "X30AYTWXRKLTWP0X"; // Your write API Key

void setup()
{
  Serial.begin(9600);
  // set the speed and acceleration
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(100);
  // set target position
  stepper.moveTo(stepsPerRevolution);


  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
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
  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);

  // // check current stepper motor position to invert direction
  // if (stepper.distanceToGo() == 0){
  //   stepper.moveTo(-stepper.currentPosition());
  // }
  // // move the stepper motor (one step at a time)
  // stepper.run();

  delay(1000);
}
