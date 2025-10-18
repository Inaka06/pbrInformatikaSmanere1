#include <WiFi.h>
#include <HTTPClient.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Sumber firebase database
const String firebaseUrl = "";  // url firebase masukkan sini

int ledPin = 2; // Pin LED

void setup() {
  // Start serial communication
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  // Status WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  HTTPClient http;

  http.begin(firebaseUrl);  // fetch data firebase

  int httpCode = http.GET();  

  if (httpCode == 200) {  
    String payload = http.getString();
    Serial.println("Received data from Firebase:");
    Serial.println(payload);  

    if (payload == "true") {
      Serial.println("Turn ON LED");
      digitalWrite(ledPin, HIGH); //hidupkan LED
    } else if (payload == "false") {
      Serial.println("Turn OFF LED");
      digitalWrite(ledPin, LOW); //matikan LED
    }
  } else {
    Serial.println("Error on HTTP request"); //handle error
  }

  http.end();  


  delay(1000); //delay 1000ms
}

