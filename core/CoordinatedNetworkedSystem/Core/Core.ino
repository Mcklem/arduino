#include <ArduinoJson.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

EthernetClient client;
EthernetServer server(80);

unsigned long refreshIPtimer = 0;

String HTTP_request = "";

void setup() {
  Serial.begin(9600);
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
 
    Wire.requestFrom(42, 150);//request wire data
    String message = "";
    while (Wire.available()> 0) { // loop through all but the last
      byte c = Wire.read();
      Serial.print(c);
      message.concat((char)c); // receive byte as a character
    }
    Serial.println(message);
    //client.println(WireControl::readWireMessage());
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



