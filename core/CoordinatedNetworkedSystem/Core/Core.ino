#include <ArduinoJson.h>
#include <Ethernet.h>
#include <Wire.h>
#include "./WireControl.h"

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

EthernetClient client;
EthernetServer server(80);

unsigned long refreshIPtimer = 0;

String HTTP_request = "";

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  initializeEthernet();
}

void initializeEthernet(){
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
  }
  Serial.println(Ethernet.localIP());
  server.begin();
}
/*
void sendRequest(){
  Wire.requestFrom(8, 100);    // request 6 bytes from slave device #8

  String message = "";
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    message.concat(c);         // print the character
  }
}*/

void loop() {
  refreshIP();
  acceptEthernetClients();
  delay(10);
}

void acceptEthernetClients() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (HTTP_request.length() < 100) {
          //store characters to string
          HTTP_request += c;
          //Serial.print(c);
        }

         //if HTTP request has ended
         if (c == '\n') {          
           //Serial.println(HTTP_request); //print to serial monitor for debuging
           client.println(F("HTTP/1.1 200 OK")); //send new page
           client.println(F("Content-Type: text/html"));
           client.println();     
           writeHTTP(client);
           delay(1);
           //stopping client
           client.stop();
         }
       }
    }
  }
}

void refreshIP(){
  if(millis()>=refreshIPtimer){
    Ethernet.maintain();
    //Serial.println("IP Renovada: " + (String)Ethernet.maintain());
    refreshIPtimer = millis() + (1000 * 30);//CADA 30 SEGUNDOS
  }
}

void writeHTTP(EthernetClient client){

    unsigned int timeSinceStart = millis()/1000;

  //prepare data
    String a = "50";
    byte b[sizeof(a)];
    byte bytes[32];
    a.getBytes(b,sizeof(a));

    //send
    requestData(42,b,bytes);

    //receive  
    String message = "";
    for(int i = 0;i<32;i++){
      char c = (char) bytes[i];
      message.concat(c);
      Serial.print(c);
    }
    Serial.println();
    
    client.println("<head></head>"); 
    client.println("<body>"); 
    client.println(message);
    client.println("</body>");  
}

bool getHTTPRequest(String request){
    bool r = HTTP_request.indexOf(request) > 0;
    if(r)HTTP_request = "";
    return r;
}

//Cant be sent or received more than 32 bytes in a single call
void requestData(int device , byte dataToBeSent[], byte receivedData[]){
    Wire.beginTransmission(device);
    Wire.write(dataToBeSent, sizeof(dataToBeSent));
    Wire.endTransmission();
    Wire.requestFrom(device, sizeof(receivedData));//request wire data
    short i = 0;
    while(Wire.available()>0){
      receivedData[i++] = Wire.read();
    }
}



