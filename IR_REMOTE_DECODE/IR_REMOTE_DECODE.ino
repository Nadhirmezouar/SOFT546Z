
// using this script to decode the ir remote inputs and defining buttons
// hex numbers to control the robot.
#include <IRremote.h> // include IR REMOTE Library

const int RECV_PIN = 7; //IR Receiver Pin

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true); // Arduino builtin LED to notify each click
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX); // displaying HEX values of buttons
        irrecv.resume();
  }
}
