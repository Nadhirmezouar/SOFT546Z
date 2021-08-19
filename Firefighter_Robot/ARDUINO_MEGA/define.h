//Defining ESP32_DEV to RX1-TX1 mega pins
#define EspSerial Serial2 //using pins 16,17

//Sensor pins
#define FlameSen1 2 // connect DO pin of sensor to this pin
#define FlameSen2 3 // connect DO pin of sensor to this pin
#define FlameSen3 4 // connect DO pin of sensor to this pin
#define FlameSen4 5 // connect DO pin of sensor to this pin
#define FlameSen5 6 // connect DO pin of sensor to this pin
#define Alarm 7 // pin 8 for Alarm 
#define WaterPowerPin 8
#define Watersen A2
#define smokesen A0

//Define DHT22 to read Temperature
#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Value to store water level
int waterval = 0;

int counter = 0;
//value to store Smoke Sensor
int smoke = 0;

float t;
