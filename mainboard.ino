#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHTesp.h>

//wifi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

//api write thingspeak
unsigned long channelID = ;  
const char* writeAPIKey = "";  

const int DHT_PIN = 15;  
DHTesp dhtSensor;

WiFiClient client;

void setup() {
  Serial.begin(115200); //start
  
  //status wifi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  //setup dht22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  //initiate thingspeak
  ThingSpeak.begin(client);
}

void loop() {

  //ambil data dari dht22
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temperature = data.temperature;
  float humidity = data.humidity;

  //(opsional) print ke console
  Serial.println("Temp: " + String(temperature, 2) + "°C");
  Serial.println("Humidity: " + String(humidity, 1) + "%");
  Serial.println("---");

  //kirim data ke thingspeak
  ThingSpeak.setField(1, temperature);  
  ThingSpeak.setField(2, humidity);    

  //definisikan field
  int httpResponseCode = ThingSpeak.writeFields(channelID, writeAPIKey);
  
  //status pengiriman data
  if (httpResponseCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.println("Error sending data to ThingSpeak: " + String(httpResponseCode));
  }

  //thingspeak punya cooldown 15 detik, kirim data setiap 20 detik
  delay(20000);
}
