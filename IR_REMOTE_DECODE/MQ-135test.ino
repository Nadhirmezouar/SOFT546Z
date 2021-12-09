int const BUZZER = 4; // Digital connected Pin
int sensorThres = 500; // Sensor Readings Threshold

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(20);
  if (sensorValue > sensorThres)
  {
    tone(BUZZER, 1000, 200);
  }
  else
  {
    noTone(BUZZER);
  }
}
