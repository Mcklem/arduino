#include <ArduinoJson.h>
#include <Ethernet.h>
#include <Wire.h>

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
    int device = 14;
    
    char dataToBeSent[] = {'1','5'};//A1 of device 14
    byte receivedData[32];
    //send requestData
    Serial.print(sizeof(dataToBeSent));
    Serial.println();
    Wire.beginTransmission(device);
    Wire.write(dataToBeSent, sizeof(dataToBeSent));
    Wire.endTransmission();
    Wire.requestFrom(device, sizeof(receivedData));//request wire data
    short i = 0;
    while(Wire.available()>0){
      receivedData[i++] = Wire.read();
    }

    //receive response
    String message = "";
    for(int i = 0;i<32;i++){
      char c = (char) receivedData[i];
      message.concat(c);
      Serial.print(c);
    }

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    root["device"] = device;
    JsonObject& data = root.createNestedObject(F("data"));
    data["time"] =  millis()/1000;
    data["15"] = message;
    String jsonStr = "";
    root.prettyPrintTo(jsonStr);
    
    Serial.println();
    client.println("<!DOCTYPE html><html>"); 
    client.println("<head></head>"); 
    client.println("<body>"); 
    client.println(jsonStr);
    client.println("</body>");  
    client.println("</html>"); 
}

bool getHTTPRequest(String request){
    bool r = HTTP_request.indexOf(request) > 0;
    if(r)HTTP_request = "";
    return r;
}
