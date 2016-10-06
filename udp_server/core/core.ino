/* IMPORTANT: ARDUINO BOARD + ETHERNET SHIELD + INTERNET CONNECTION
 * You only need to known the ARDUINO IP and port(default 8888)
 */

#include <SPI.h>                  // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>          // UDP library from: bjoern@cs.stanford.edu 12/30/2008

//TODO Structs into libraries
struct Address{
  IPAddress ip;
  unsigned int port;

  Address() : ip(IPAddress{0,0,0,0}), port(0){}
  Address(IPAddress _ip,unsigned int _port) : ip(_ip), port(_port){}

  bool isNull(){
    return ip==IPAddress{0,0,0,0} || port==0;
  }
  
};

struct UDPMessage{
  String data;
  Address address;

  bool hasBeenSent(){
    return data!="" && address.port!=0 && address.ip!=IPAddress{0,0,0,0};
  }
};

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
EthernetUDP Udp;


unsigned int localPort = 8888;      // local port to listen on
Address addresses[3];

unsigned long sendTimer = 0;

// buffers for receiving and sending data

void setup() {
  Serial.begin(9600);
  initializeEthernet();
  initializeUDP();
}

void initializeEthernet(){
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  Serial.println(Ethernet.localIP());
}

void initializeUDP(){
  //Inicializamos las maquinas
  Udp.begin(localPort);
}

bool addMachine(Address address){
  unsigned int s = sizeof(addresses)/8;
      Serial.println("Hay un espacio máximo para " + (String)s + " máquinas.");
       
      for(int i =0;i<s;i++){ 
        if(addresses[i].isNull()){
          addresses[i] = address;
          break;
        }
        if(i>=s-1){
           Serial.println("No se pueden añadir más máquinas, el sistema está completo.");
        }
      }
      Serial.println("Added succesfully."); 
}

void loop() {
  UDPMessage message = readUDPMessage();
  if(message.hasBeenSent()){
    String r = message.data;
    r.trim();
    r.toLowerCase();
    
    if(r=="a"){
      addMachine(message.address);
    }
    if(r=="b"){
      //removeMachine(message.address);
    }
    if(r=="c"){
      showCurrentMachines();
    }
  }

  sendResponse();

  delay(10);
}

void sendResponse(){
  if(millis()>=sendTimer){

    for(int i = 0; i<sizeof(addresses)/8;i++){
      if(!addresses[i].isNull()){
        sendUDPMessage("Response Test...", addresses[i].ip, 8888);
      }
    }
    sendTimer = millis() + 1000;
  }
}

void showCurrentMachines(){
  Serial.println("CURRENT MACHINES:");
  for(int i =0;i<sizeof(addresses)/8;i++){
    Serial.println(stringFromIP(addresses[i].ip));
  }
}

UDPMessage readUDPMessage(){
  // if there's data available, read a packet
  char packetBuffer[UDP_TX_PACKET_MAX_SIZE];//Clear buffer
  int packetSize = Udp.parsePacket();
  IPAddress remote_ip;
  UDPMessage message;
  unsigned int remote_port = 0;
  if (packetSize) {
    remote_ip = Udp.remoteIP();
    remote_port = Udp.remotePort();
  
    Serial.println("Received packet of size " + (String) packetSize + " bytes");
    Serial.println("From " + stringFromIP(remote_ip) + ", port " + (String)remote_port);
      
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
      
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    Serial.println();

    message = (UDPMessage){packetBuffer, Address(remote_ip, remote_port)};
  }
  return message;
}

void sendUDPMessage(char message[], IPAddress ip, int port){
    Serial.print("Sending reply to " + stringFromIP(ip) + ":");
    Serial.println(port);
    
    if(Udp.beginPacket(ip, port)) Serial.println("host solved properly");
    else Serial.println("error solving the host");
    
    Serial.println("message size: " + (String) Udp.write(message));
    
    if(Udp.endPacket()) Serial.println("message was sent succesfully");
    else Serial.println("error sending message"); 
}

String stringFromIP(IPAddress remote){
  String s;
  for (int i = 0; i < 4; i++) {
      s += (String)(int)remote[i];
      if (i < 3) {
        s += ".";
      }
   }
   return s;
}

String *split(String data){
  int s = 0;
  for(int i = 0;i<sizeof(data);i++){
    if((int)data[i]==32) s++;
  }
  String r[s];
  int rindex = 0;
  for(int i = 0;i<sizeof(data);i++){
    r[rindex] = i + r[rindex] + data[i];
    if((int)data[i]==32)rindex++;   
  }
  return r;
}

