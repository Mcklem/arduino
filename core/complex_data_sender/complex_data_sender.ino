#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

IPAddress mysqlServerAddress(192,168,1,37);
char user[] = "root";
char password[] = "23jes0894";

EthernetClient client;
MySQL_Connection connection((Client *)&client);

unsigned long sendTimer = 0;

char INSERT_DATA[] = "INSERT INTO arduino.input_data (type, data, date) VALUES ('%s','%s',NOW())";
char query[256];

void setup() {
  initializeSerial();
  initializeEthernet();
  initializeMySQL();
}

void initializeSerial(){
  Serial.begin(9600);//Si iniciamos el puerto serie, esto no avanza hasta establecer una conexion con un puerto serie
}

void initializeEthernet(){
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
  }
  Serial.println(Ethernet.localIP());
}

void initializeMySQL(){
  Serial.println(F("Connecting with mysql server..."));
  if(connection.connect(mysqlServerAddress, 3306, user, password)){
    Serial.println(F("Connected with mysql successfully."));
  }
  else{
    Serial.println(F("Connecion failed."));
    connection.close();
  }
}

void loop() {

  if(millis()>=sendTimer){
    if(!connection.connected()){
      Serial.println(F("Still not connected..."));
      initializeMySQL();
      delay(5000);
    }  
    
    sprintf(query, INSERT_DATA, "TEST", "{}");
    
    mysqlInsert(query);
    
    sendTimer = millis() + 1000;
  }
  
}

void mysqlInsert(char query[]){
    MySQL_Cursor *currentCursor = new MySQL_Cursor(&connection);
    currentCursor->execute(query);
    delete currentCursor;
    Serial.println(query);
}





