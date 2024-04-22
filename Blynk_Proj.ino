#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 4           // DHT11 sensor pin
#define DHTTYPE DHT11      // DHT type
#define SOIL_MOISTURE_PIN A0  // Soil moisture sensor pin
#define PIR_PIN 2          // PIR motion sensor pin

char auth[] = "MyProject";
char ssid[] = "MyProject";
char pass[] = "12345678";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int motionDetected = digitalRead(PIR_PIN);

  Blynk.virtualWrite(V5, humidity);       // Virtual pin V5 for humidity
  Blynk.virtualWrite(V6, temperature);    // Virtual pin V6 for temperature
  Blynk.virtualWrite(V7, soilMoisture);   // Virtual pin V7 for soil moisture
  Blynk.virtualWrite(V8, motionDetected); // Virtual pin V8 for motion detection
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(10000L, sendSensorData); // Send sensor data every 10 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
