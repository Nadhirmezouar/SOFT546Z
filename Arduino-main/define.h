
//define Serial:
#define EspSerial Serial

//define remote control buttons:
#define f  0xFF18E7 // code received from forward  button
#define b  0xFF4AB5 // code received from backward button
#define l  0xFF10EF // code received from left button
#define r  0xFF5AA5 // code received from right button
#define s  0xFF38C7 // code received from (OK)stop button
#define h  0xFFA25D // code received from Number 1 button
#define t  0xFF629D // code received from Number 2 button
#define e  0xFFE21D // code received from Number 3 button
#define g  0xFF22DD // code received from Number 4 button

//define DHT22 Sensor:
#define DHTPIN A0     // Analog connected pin
#define DHTTYPE DHT22   // DHT 22  choice


//declare Temperaure and Humidity:
float hum;  //Stores humidity value
float temp; //Stores temperature value

//declare Smoke Sensor and Sensor Theshold:
int smoke = A1; // Analog connected Pin
int sensorThres = 500; // Sensor Readings Threshold


// Motors Configurations:
//  Motor 1 Pins:
int const ENA = 10;  
int const INA = 12;
//  Motor 2 Pins:
int const ENB = 11;  
int const INB = 13;

//declare IR Remote Controller:
int rec = 7;   // Digital connected Pin


//declare Buzzer:
int const BUZZER = 4; // Digital connected Pin

int counter = 0; // used in Sending Data loop
