   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>


char auth[] = "";//Add Authorisation Key from Blynk App Channel 


char ssid[] = "";//Add WiFi name  
char pass[] = "";//Add Password (To be Left Empty for Open Networks)  
#define DHTPIN 0          


 

DHT dht(DHTPIN, DHT11);
SimpleTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Blynk.virtualWrite(V5, h);  
  Blynk.virtualWrite(V6, t);  
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();


  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); 
  timer.run(); 
}
