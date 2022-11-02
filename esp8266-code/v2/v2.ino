#include "ThingSpeak.h"
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
	
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "realmeX2"; //SSID
char pass[] = "123456798"; // Password
//-------------------------------------------//

const int trigger = D6;
const int echo = D7;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField = 1884400; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "X30AYTWXRKLTWP0X"; // Your write API Key

void setup()
{
  Serial.begin(9600);
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
  delay(1000);
}
