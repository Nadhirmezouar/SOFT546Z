#include "define.h" // including Defined configuration file
#include <IRremote.h>   // including the IR remote library
#include <LiquidCrystal_I2C.h> // including LCD Library
#include <Wire.h> // including Wire Library
#include <DHT.h>; // including DHT22 Sensor Library
#include <EasyTransfer.h> // including Serial EasyTransfer Library

//creating Serial Object
EasyTransfer ET;

//sending data array
struct SEND_DATA
{
  float temperature;
  float humidity;
  float smokesensor;
};

//initiate sending data name
SEND_DATA data;

//initiate IR Remote receive function
IRrecv receiver(rec); //take output of IR receiver from defined pin
decode_results output;

//initiate LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize DHT22 Sensor Type and Pin
DHT dht(DHTPIN, DHTTYPE); 


void setup()
{
  //initializing Serial
  EspSerial.begin(115200);
  ET.begin(details(data), &EspSerial);
  
  //initializing IR Remote receiver
  receiver.enableIRIn();  // Start to take the output from IR receiver
  
  //initializing all pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  //initializing all pins as intput pins
  pinMode(smoke, INPUT);
  
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  
 //initialize DHT22 Sensor
  dht.begin();
  
}


void loop() {

  //Reading Sensors Values
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  int smokesen = analogRead(smoke);

  //Smoke Sensor Alert function
  if (smokesen > sensorThres)
  {
    alert();
  }
  else
  {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press");
    lcd.setCursor(0,1);
    lcd.print("Any Button");
    delay(10);
  }
  
  //sending the data
      counter ++;
  if (counter == 8) //Send data once every two seconds
  { //storing data into variables
  data.temperature = temp;
  data.humidity= hum;
  data.smokesensor= smokesen;
    ET.sendData();
    counter = 0;
  }
 delay(150);

   // IR Remote receiver buttons functions to actions
   if (receiver.decode(&output)) { 
    unsigned int value = output.value;
    switch(value) {
     
  case f://Moving Forward
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Command");
  lcd.setCursor(0,1);
  lcd.print("Forward");
  delay(500);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH); 
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
          break;
       
  case b: //Moving backward
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Command");
  lcd.setCursor(0,1);
  lcd.print("Backward");
  delay(500);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH); 
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
  delay(100);  
  digitalWrite(BUZZER, LOW);
         break;

  case l://Turning left
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Command");
  lcd.setCursor(0,1);
  lcd.print("Left");
  delay(500);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH); 
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
          break;  
        
  case r://Turning Right
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Command");
  lcd.setCursor(0,1);
  lcd.print("Right");
  delay(500);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH); 
  digitalWrite(INA, HIGH);
  digitalWrite(INB, HIGH);
          break;
       
  case s://Stop
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Command");
  lcd.setCursor(0,1);
  lcd.print("Stop");
  delay(500);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW); 
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
          break;

  case h: //Buzzer Test
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
  delay(100);  
  digitalWrite(BUZZER, LOW);
  delay(100);
  break;

  case t: //Display Temperature
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(2000);
  break;

  case e://Display Humidity
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity");
  lcd.setCursor(0,1);
  lcd.print(hum);
  delay(2000);
  break;

  case g://Display Gas 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gas");
  lcd.setCursor(0,1);
  lcd.print(smokesen);
  delay(2000);
  break;

  default:
  break;
  
      }
    Serial.println(value);
    receiver.resume();
    }
 }

 void alert(){ //Gas Smoke Alert 
    tone(BUZZER, 1000, 200);
    delay(10);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WARNING");
    lcd.setCursor(0,1);
    lcd.print("Smoke");
  }
