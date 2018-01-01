/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * to control GPIO (on-board LED)
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char* www_username = "admin";
const char* www_password = "admin";

const char *ssid = "IM_NOT_AN_ACCESS_POINT";
const char *password = "12345678";
int stateLED = LOW;
bool blinkState = false;
#define led_pin 16

ESP8266WebServer server(80);

const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>Arduino-er: ESP8266 AP WebServer exercise</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>ON</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>OFF</b></big><br/>\n";
const String HtmlButtons = 
    "<a href=\"LEDOn\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LEDOff\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
    "<a href=\"Hello\"><button style=\"display: block; width: 100%;\">HELLO</button></a><br/>";

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("Address: ");
    Serial.println(apip);

    server.onNotFound(handleNotFound);
    //server.on("/", handleRoot);
    server.on("/", [](){
    if(!server.authenticate(www_username, www_password))
      return server.requestAuthentication();
      handleRoot();
    });
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);
    server.on("/Hello", handleHello);
    server.on("/Time", handleTime);
    server.on("/StationNumber", handleStationNum);
    server.on("/Info", handleWifiInfo);
    server.on("/DeviceInfo", handleDeviceInfo);
    server.begin();
    Serial.println("HTTP server beginned");
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, stateLED);
}

void handleDeviceInfo(){
  Serial.println(ESP.getBootVersion());
  Serial.println(ESP.getBootMode());
  Serial.println(ESP.getCpuFreqMHz());
  Serial.println(ESP.getSketchSize());
  Serial.println(ESP.getFreeSketchSpace());
  Serial.println(ESP.getFreeHeap());
  Serial.println(ESP.getChipId());
  Serial.println(ESP.getFlashChipId());
  Serial.println(ESP.getFlashChipSize());
  Serial.println(ESP.getCycleCount());
  Serial.println(ESP.getVcc());
  /*if (WiFi.status() == WL_CONNECTED)
  {
    char buffer [18];
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    sprintf(buffer, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    htmlRes += buffer;
  }*/
  server.send(200, "text/html", "");
}

void handleWifiInfo(){
  String htmlRes = "";
  //WiFi.printDiag(htmlRes);
  htmlRes += WiFi.localIP();
  htmlRes += WiFi.getMode();
  htmlRes = HtmlHtml + htmlRes + HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
}

void handleNotFound(){
  String htmlRes = HtmlHtml;
  htmlRes += "<h1> Oops, 404 page not found. </h1>";
  htmlRes += HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
}

void handleRoot() {
    response();
}

void handleLedOn() {
  stateLED = LOW;
  digitalWrite(led_pin, stateLED);
  response();
}

void handleLedOff() {
  stateLED = HIGH;
  digitalWrite(led_pin, stateLED);
  response();
}

void handleHello() {
  Serial.println("Hello darkness my old friend");
  response();
}

void handleTime() {
  String htmlRes = HtmlHtml;
  int t = millis()/1000;
  htmlRes += String(t)  + "s";
  htmlRes += HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
}

void handleStationNum(){
  String htmlRes = HtmlHtml;
  htmlRes += String(WiFi.softAPgetStationNum())  + " devices";
  htmlRes += HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
}

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;

  if(stateLED == LOW){
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}


void loop() {
    server.handleClient();
    delay(100);
}
