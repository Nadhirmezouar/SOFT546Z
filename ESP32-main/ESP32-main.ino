#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <EasyTransfer.h>

// Network credentials
const char* ssid = "Network Name";
const char* password = "Password";

//create Serial object
EasyTransfer ET; 

//recieving data array
struct RECEIVE_DATA
{
  float temperature;
  float humidity;
  float smokesensor;
};

//initiate recieving data name
RECEIVE_DATA data;

//declare Temperaure, Humidity and smoke:
float temp;
float hum;
float smo;

// initiate AsyncWebServer object on port 80
AsyncWebServer server(80);


// create webpage layout
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 20px;
    }
  </style>
</head>
<body>
  <h2>Buggy Environment Monitor</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <i class="fas fa-smog" style="color:#b0a7a4;"></i> 
    <span class="labels">Smoke</span>
    <span id="smoke">%SMOKE%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>//webpage functions setup
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("smoke").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/smoke", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replacing webpage wordholders with receiving values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(temp);
  }
  else if(var == "HUMIDITY"){
    return String (hum);
  }  
  else if(var == "SMOKE"){
    return String (smo);
  }
  return String();
}

void setup(){
  //initializing Serial
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  ET.begin(details(data), &Serial);

  //initializing Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Diplaying Local IP Address
  Serial.println(WiFi.localIP());

  // Route for webpage of each value
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(temp).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String (hum).c_str());
  });
  server.on("/smoke", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String (smo).c_str());
  });

  // initializing server
  server.begin();
}
 
void loop(){

//receiving and storing the data
if(ET.receiveData()){
    temp = data.temperature;
      Serial.println(" Temperature :");
      Serial.println(temp);
      Serial.print("\t"); 
    hum= data.humidity;   
      Serial.println(" Humidity :");
      Serial.println(hum);
      Serial.print("\t"); 
    smo= data.smokesensor;
      Serial.println(" Smoke :");
      Serial.println(smo);
      Serial.print("\t");
      Serial.println();
      Serial.flush(); 
}
  delay(100);
}
