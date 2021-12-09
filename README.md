# SOFT546Z coursework:
#### The aim of this project, is to design and interactive distributed system. Buggy Robot monitoring the environment is a distributed system which interacts with the operator using IR Remote controller, LCD screen and Webpage diplaying sensors measurments in realtime.
## Repository Overview:
> SOFT564Z: Github Repository
<br>
<br>
>> Arduino-main: Arduino source code, used to control buggy movement and sensor readings, as well as the serial communication with ESP32.
<br>
<br>
>>> define.h: defining all sensors and libraries variables.
<br>
<br>
>> ESP32-main: ESP32 source code, used to receive sensors data from arduino and display it on local webpage using ESP32 server.
<br>
<br>
>> IR_REMOTE_DECODE: IR Remote source code,used to read HEX values of pressed buttons so we can program the robot actions.this file is set for IR sensor Test and DHT22 Temperature and Humidity Sensor Test and MQ-135 Gas Sensor Test.
<br>
<br>
>> circuit.png/jpg: Fritzing picture for the robot electrical connection.
<br>
<br>

## Instructions:
To start using the robot: 
<br>
<br>
1-Download the repository to your PC.
<br>
<br>
2-Open SOFT564Z and upload Arduino-main to arduino Uno.
<br>
<br>
3-Open SOFT564Z and upload ESP32-main to ESP32 Board and setup WIFI name and password in the source code.
<br>
<br>
4-Use IR_REMOTE_DECODE source file to update your IR Remote control buttons HEX Values in Arduino-main.
<br>
<br>
5-Follow the GPIO connection privded in circuit.png and switch on powersupply.
<br>
<br>
6-While Connecting ESP32 With Serial Monitor, Local IP Address will be provided after WIFI is connected.
<br>
<br>
7-Open browser with the given local IP Address and the check sensors readings from both LCD and webpage in realtime.
<br>
<br>
8- Use arrows to move the robot and enjoy playing with it.

## Hardware Used:
1- Arduino Uno
<br>
<br>
2- l298P Motor shield
<br>
<br>
3- ESP32 D1 R32 Board
<br>
<br>
4- MQ-135 Gas Sensor
<br>
<br>
5- DHT22 Sensor
<br>
<br>
6- LCD Screen
<br>
<br>
7- 2x 9v Battery
<br>
<br>
8- IR Remote Receiver and Controller
<br>
<br>

## Videos:
1-https://youtu.be/sAK6A7Ta8fA
<br>
<br>
Explainig Hardware connection and choice of hardware.
<br>
<br>
2-https://youtu.be/iOC_t9_sarY
<br>
<br>
Explaining the functionality of the robot.
