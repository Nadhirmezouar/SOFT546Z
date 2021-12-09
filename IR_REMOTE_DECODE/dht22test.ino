#include "DHT.h"

#define DHTPIN A0

//define DHTTYPE DHT22  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

int timeSinceLastRead = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 test!");

  dht.begin();
}

void loop() {

 // Report every 2 seconds.
  if(timeSinceLastRead > 2000) {
    // Reading temperature or humidity
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }



    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print("\t");
    Serial.println();
    Serial.flush();


    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
