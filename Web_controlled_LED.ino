#include <ESP8266WebServer.h>

#define LEDn    D6
#define LEDpwm  D2

const char* ssid = ""; // Name of the server

const char* password = ""; // Password of minimum 8 characters


ESP8266WebServer server(80);

char webpage[] = R"=(
<html>
<head>
    <title> Controller </title>
    <style = "text/css">
    .slidecontainer {
  width: 100%; 
}

.slider {
  -webkit-appearance: none; 
  appearance: none;
  width: 100%; 
  height: 25px;
  background: #000000;
  outline: none; 
  opacity: 0.7; 
  -webkit-transition: .2s;
  transition: opacity .2s;
}
.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none; 
  appearance: none;
  width: 25px; 
  height: 25px; 
  background: #FF0000;
  cursor: pointer; 
}

.slider::-moz-range-thumb {
  width: 25px; 
  height: 25px;
  background: #FF0000;
  cursor: pointer; 
}
</style>
</head>    
<body>  
 
 <div class="slidecontainer">
  <input type="range" min="0" max="1023" value="0" class="slider" id="myRange">
  <p>Value: <span id="demo"></span></p>
</div>
</body>
<script>
var slider = document.getElementById("myRange");

var output = document.getElementById("demo");

output.innerHTML = slider.value;

slider.onchange = function() {
  output.innerHTML = this.value;
  pwm_change(output.innerHTML);
}
function pwm_change(val) {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "setPWM?PWMval="+val, true);
     xhttp.send();
}
</script>
</html>
)=";
int pwm;
int pwmCount;
void handle_pwm() {
 String  pwm_val = server.arg("PWMval"); 

 Serial.print("slider val: ");
 Serial.println(pwm_val);
int pwm_value = pwm_val.toInt(); 
pwm= pwm_value;

server.send(200,"text/plane","0"); 

}

void handleRoot(){
  server.send(200, "text/html", webpage);  
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDn,OUTPUT);
  pinMode(LEDpwm,OUTPUT);
  WiFi.mode(WIFI_AP);
  IPAddress apLocalIp(2,2,2,2);
  IPAddress apSubnetMask(255,255,255,0);
  WiFi.softAPConfig(apLocalIp,apLocalIp,apSubnetMask);
  WiFi.softAP(ssid, password);
  server.begin();
  server.on("/", handleRoot); 
  server.on("/setPWM", handle_pwm); 
  pwm=0;
  pwmCount=0;
}

void loop() {
  server.handleClient();
  
  Serial.println(pwm);
  analogWrite(LEDpwm, pwm);
  delay(10);
}
