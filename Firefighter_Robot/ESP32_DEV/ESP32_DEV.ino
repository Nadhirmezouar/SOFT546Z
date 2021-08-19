//Blynk App Refrence
#define BLYNK_TEMPLATE_ID "TMPLzTcPm8ol"
#define BLYNK_DEVICE_NAME "Firefighter Robot"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <EasyTransfer.h>
#include <ESP32Servo.h>

#define USE_WROVER_BOARD

#include "BlynkEdgent.h"


// L298N Motor driver pinout
#define MOTOR_1_PIN_1    34
#define MOTOR_1_PIN_2    35
#define MOTOR_2_PIN_1    32
#define MOTOR_2_PIN_2    33

//Watergun Pump
#define Pump 25



WidgetLCD lcd(V0);
BlynkTimer timer;
Servo hs;
Servo vs;

// Intiate EasyTransfer Library as ET
EasyTransfer ET;
//EasyTransfer Recieve Varible
struct RECEIVE_DATA
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
RECEIVE_DATA data;

//define Vaiables to send to Blynk
float t;
int w;
int fs1;
int fs2;
int fs3;
int fs4;
int fs5;
int s;
int wl;
int ss;
//----------------------------------------Receive Data and Read-------------------------------------
void SensorsData()
{
  if (ET.receiveData()) {
    t = data.temperature;
    w = data.waterlevel;
    fs1 = data.flamesensor1;
    fs2 = data.flamesensor2;
    fs3 = data.flamesensor3;
    fs4 = data.flamesensor4;
    fs5 = data.flamesensor5;
    s = data.smokesensor;
  }
  delay(200);
  //Map Water level Sensor Readings
  wl = map(w, 1023, 0, 100, 0);
  //Map Smoke Sensor Readings
  ss = map(s, 1023, 0, 100, 0);

  //Read and send Sensor data to Blynk App
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, wl);
  Blynk.virtualWrite(V6, ss);

}
//---------------------------------------------Setup--------------------------------

void setup()
{
  Serial.begin(115200);
  delay(100);
  ET.begin(details(data), &Serial);

  hs.attach(26);
  hs.attach(27);

  pinMode(Pump, OUTPUT); //Set PUMP Pin Motor as OUTPUT
  digitalWrite(Pump, LOW); //Set PUMP Pin Motor off
  

  // Setup the pins for the motors
  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_1_PIN_2, OUTPUT);
  pinMode(MOTOR_2_PIN_1, OUTPUT);
  pinMode(MOTOR_2_PIN_2, OUTPUT);
  
  BlynkEdgent.begin();
  

  timer.setInterval(1000L, SensorsData); //timer will run every sec to read Data
}
//----------------------------------------Main-------------------------------------

void loop() {
  BlynkEdgent.run();
  timer.run();
}

//--------------------------------------------------Blynk Virtual LCD---------------------------

BLYNK_WRITE(V0) // LCD
{
  if (fs1 == 1 || fs2 == 1 || fs3 == 1 || fs4 == 1 || fs5 == 1)
  {
        lcd.clear();
        lcd.print(6, 0, "WARNING");
        lcd.print(6, 1, "FIRE!");
  }
  else if (ss >= 60)
  {
        lcd.clear();
        lcd.print(1, 0, "WARNING");
        lcd.print(1, 1, "SMOKE!");

    }

    
  }
//---------------------------Blynk Robot Control Buttons--------------------------------------------------

BLYNK_WRITE(V8) // Forward
{
    int i=param.asInt();
    if (i==1) 
    {
        lcd.clear();
        lcd.print(5, 0, "Moving");
        lcd.print(5, 1, "Forward");
        Forward();
    }
    else 
    {
        lcd.clear();
        lcd.print(5, 0, "Stopped");
        Stop();
    };
}

BLYNK_WRITE(V11) // Right
{
    int i=param.asInt();
    if (i==1) 
    {
        lcd.clear();
        lcd.print(5, 0, "Moving");
        lcd.print(5, 1, "Right");
        Right();
    }
    else 
    {
        lcd.clear();
        lcd.print(5, 0, "Stopped");
        Stop();
    };
}

BLYNK_WRITE(V10) // Left
{
    int i=param.asInt();
    if (i==1) 
    {
        lcd.clear();
        lcd.print(5, 0, "Moving");
        lcd.print(5, 1, "Left");
        Left();

    }
    else 
    {
        lcd.clear();
        lcd.print(5, 0, "Stopped");
        Stop();
    };
}

BLYNK_WRITE(V9) // Backward
{
    int i=param.asInt();
    if (i==1) 
    {
        lcd.clear();
        lcd.print(5, 0, "Moving");
        lcd.print(5, 1, "Backward");
        Backward();
    }
    else 
    {
        lcd.clear();
        lcd.print(5, 0, "Stopped");
        Stop();;
    };
}


//-------------------------------------------Blynk Move Horizontal Servo----------------------------------

BLYNK_WRITE(V5) // Horizontal Servo
{
  hs.write(param.asInt());
}

//-----------------------------------------------Blynk Move Vertical Servo------------------------------

BLYNK_WRITE(V6) // Vertical Servo
{
  vs.write(param.asInt());
}

//---------------------------------------------------Blynk Pump Push Button--------------------------

BLYNK_WRITE(V7) //Pump Button
{
    int i=param.asInt();
    if (i==1) 
    {
        lcd.clear();
        lcd.print(3, 0, "WaterGun");
        lcd.print(6, 1, "ON");
        digitalWrite(Pump, HIGH);
    }
    else 
    {
        digitalWrite(Pump, LOW);
    }
}

//-----------------------------------------------Motor Drive Functions------------------------------
void Forward() {
    digitalWrite(MOTOR_1_PIN_1, 1);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 1);
    digitalWrite(MOTOR_2_PIN_2, 0);
}

void Left() {
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 1);
    digitalWrite(MOTOR_2_PIN_1, 1);
    digitalWrite(MOTOR_2_PIN_2, 0);
}

void Right(){
    digitalWrite(MOTOR_1_PIN_1, 1);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 1);
}

void Stop(){
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 0);
}

void Backward(){
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 1);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 1);
}
