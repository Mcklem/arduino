#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
EthernetServer server(80);

unsigned long refreshIPtimer = 0;

String HTTP_request = "";

int led = 4;

void setup() {
  //Serial.begin(9600);//Si iniciamos el puerto serie, esto no avanza hasta establecer una conexion con un puerto serie
  pinMode(led, OUTPUT);
  initializeEthernet();
}

void initializeEthernet(){
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  Serial.println(Ethernet.localIP());
  server.begin();
}

void loop() {
  refreshIP();
  acceptEthernetClients();
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
           Serial.println(HTTP_request); //print to serial monitor for debuging
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           writeHTTP(client);
           delay(1);
           //stopping client
           client.stop();
           internalAction();
         }
       }
    }
  }
}

void internalAction(){
  //controls the Arduino if you press the buttons
  if (getHTTPRequest("?led_button_on")){
     digitalWrite(led, HIGH);
  }
  if (getHTTPRequest("?led_button_off")){
     digitalWrite(led, LOW);
  }
 
}

void refreshIP(){
  if(millis()>=refreshIPtimer){
    Serial.println("IP Renovada: " + (String)Ethernet.maintain());
    refreshIPtimer = millis() + (1000 * 30);//CADA 30 SEGUNDOS
  }
}

void writeHTTP(EthernetClient client){

    unsigned int timeSinceStart = millis()/1000;
   
    client.println("<HTML>");
    client.println("<HEAD>");
    client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
    client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
    client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
    client.println("<TITLE>HOME GUARD v0.1</TITLE>");
    client.println("</HEAD>");
    client.println("<BODY>");
    client.println("<H1>HOME GUARD</H1>");
    client.println("<hr />");
    client.println("<br />");  
    client.println("<a href=\"/?led_button_on\"\">Turn On LED</a>");
    client.println("<a href=\"/?led_button_off\"\">Turn Off LED</a><br />");   
    client.println("<br />"); 
    client.println("<hr />");    
    client.println("<br />");  
    client.println("<b> Tiempo iniciado: " + (String)timeSinceStart + " seconds </b>");
    client.println("<br />");  
    client.println("</BODY>");
    client.println("</HTML>");    
}

bool getHTTPRequest(String request){
    bool r = HTTP_request.indexOf(request) > 0;
    if(r)HTTP_request = "";
    return r;
}





