#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "hope";
const char* password = "hope87210";
WebServer server(80);

void handleSensordata(){
  int sensor=analogRead(36);
  String json="{\"vr\":";
         json+=sensor;
         json+="}";
  server.send(200,"application/json",json);  
  }
void handleRoot(){
 char website[2000];
 snprintf(website,2000,"<html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta http-equiv=\"refresh\" contest=\"5\"> <script src=\"https://code.jquery.com/jquery-2.2.4.min.js\"></script> <script>setInterval(requestData, 500); function requestData(){$.get(\"/sensors\") .done(function(data){if(data){$(\"#resis\").text(data.vr);}else{$(\"#resis\").text(\"?\");}}) .fail(function(){console.log(\"fail\");});}</script> <title>VR Reader</title></head><body> <div class=\"container\"> <p>Variable Resistor=<span id=\"resis\"></span></p></div></body></html>");
 server.send(200,"text/html",website);
  }

void setup(void){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  server.on("/sensors", handleSensordata);
  server.begin();
  Serial.println("HTTP server started");
  
  }

void loop(){
  server.handleClient();
  }
