#include <WiFi.h>
#include <HTTPClient.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Sumber firebase database
const String firebaseUrl = "";  // URL to read the state

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
  // Create an HTTPClient object
  HTTPClient http;

  http.begin(firebaseUrl);  // fetch data firebase

  int httpCode = http.GET();  // Send the GET request

  if (httpCode == 200) {  // If the request was successful
    String payload = http.getString();
    Serial.println("Received data from Firebase:");
    Serial.println(payload);  

    // Example of parsing JSON (payload will be the state as true or false)
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
