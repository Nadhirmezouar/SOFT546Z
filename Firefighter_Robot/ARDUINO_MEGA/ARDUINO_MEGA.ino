#include "DHT.h"
#include "define.h"
#include <EasyTransfer.h>

//creating object
EasyTransfer ET;

//Structure of data sent to ESP32_DEV
struct SEND_DATA
{
  float temperature;
  float waterlevel;
  float flamesensor1;
  float flamesensor2;
  float flamesensor3;
  float flamesensor4;
  float flamesensor5;
  float smokesensor;
};

//initiate name of data
SEND_DATA data;

void setup() {
  EspSerial.begin(115200);
  ET.begin(details(data), &EspSerial);
  dht.begin();
  
  //define Pins
  pinMode(Alarm, OUTPUT); //define FLAME1 digital output pin 7
  pinMode(smokesen, INPUT);//define FLAME1 analog input pin 0
  pinMode(WaterPowerPin, OUTPUT); //define FLAME1 digital input pin 8
  pinMode(FlameSen1, INPUT);//define FLAME1 digital input pin 2
  pinMode(FlameSen2, INPUT);//define FLAME2 digital input pin 3
  pinMode(FlameSen3, INPUT);//define FLAME3 digital input pin 4
  pinMode(FlameSen4, INPUT);//define FLAME4 digital input pin 5
  pinMode(FlameSen5, INPUT);//define FLAME5 digital input pin 6
  digitalWrite(WaterPowerPin, LOW);
}

void loop() {
  
  //Read Flame Sensor digital inputs
  float flame1 = digitalRead(FlameSen1);// read digital input Flame sensor 1
  float flame2 = digitalRead(FlameSen2);// read digital input Flame sensor 2
  float flame3 = digitalRead(FlameSen3);// read digital input Flame sensor 3  
  float flame4 = digitalRead(FlameSen4);// read digital input Flame sensor 4
  float flame5 = digitalRead(FlameSen5);// read digital input Flame sensor 5
  
  //Read Smoke Sensor digital inputs and map its value
  smoke = analogRead(smokesen);
  
  //Read Temperature Sensor digital inputs
  t = dht.readTemperature();
  
  //Read Water level Sensor digital inputs
  readWLS();

  //sending the data
      counter ++;
  if (counter == 8) //Send data once every two seconds
  {
  data.temperature = t;
  data.waterlevel= waterval;
  data.flamesensor1= flame1;
  data.flamesensor2= flame2;
  data.flamesensor3= flame3;
  data.flamesensor4= flame4;
  data.flamesensor5= flame5;
  data.smokesensor= ss;
    ET.sendData();
    counter = 0;
  }
 delay(150);
}

//Reading Water Level Sensor Request
int readWLS() {
  digitalWrite(WaterPowerPin, HIGH);
  delay(10);
  waterval = analogRead(Watersen);
  digitalWrite(WaterPowerPin, LOW);
  return waterval;
}
