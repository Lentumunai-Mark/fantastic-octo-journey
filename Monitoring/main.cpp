#include <Arduino.h>

/* Wifi dependencies*/
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

/*Blynk Library*/
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "Enter_Template_Id"
#define BLYNK_DEVICE_NAME "Enter_Blynk_Device_Name"
#define BLYNK_AUTH_TOKEN "Enter_Blynk_Auth_Token"
char auth[] = BLYNK_AUTH_TOKEN; // Place your Blynk applications project token code
char ssid[] = "Wifi_Name";      // Hotspot / wifi name
char pass[] = "Password";       /// Password

/*DHT Library*/
#include "DHT.h"
#define DHTPIN 17         // DHT 11 : Temperature & humidity sensor connected to digital pin D0
#define DHTTYPE DHT11     // Sensor type : DHT11
DHT dht(DHTPIN, DHTTYPE); // Send DHT pin and type parameter to DHT Function
BlynkTimer timer;
float hum = 20;  /* at init humidity is 0 */
float temp = 26; /* at init temp is 0*/
int moisture;

#define AOUT_PIN 33
#define DOUT_PIN 2
int pirState = LOW;
int val = 0;                                // initially no motion
String isMotion = "No motion Detected !!!"; // default

void sendSensorData()
{
    val = digitalRead(DOUT_PIN);
    if (val == HIGH)
    { // check if the input is HIGH
        if (pirState == LOW)
        {
            // Serial.println("Motion detected!");
            isMotion = "Motion Detected!!!";
            Blynk.virtualWrite(V3, isMotion);
            pirState = HIGH;
        }
    }
    else
    {
        if (pirState == HIGH)
        {
            // we have just turned off
            // Serial.println("Motion ended!");
            // We only want to print on the output change, not state
            isMotion = "No Motion Detected at The Moment!!!";
            Blynk.virtualWrite(V3, isMotion);
            pirState = LOW;
        }
    }
    /*
    hum = dht.readTemperature();
    temp = dht.readTemperature();
    */
    moisture = analogRead(AOUT_PIN);
    Blynk.virtualWrite(V0, hum);
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2, moisture);
}
void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    WiFi.begin(ssid, pass);
    dht.begin();
    timer.setInterval(1000L, sendSensorData);
}

void loop()
{
    Blynk.run();
    timer.run();
}