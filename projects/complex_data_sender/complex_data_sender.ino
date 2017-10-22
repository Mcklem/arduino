#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ArduinoJson.h>
#include <avr/pgmspace.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
EthernetClient client;

//MySQL
IPAddress mysqlServerAddress(192,168,1,37);
unsigned short port = 3306;
char user[] = "root";
char password[] = "23jes0894";

MySQL_Connection connection((Client *)&client);

PROGMEM const char INSERT_INPUT_DATA[] = "INSERT INTO arduino.input_data (type, data, date) VALUES ('%s','%s',NOW())";
//const char EXTRACT_DATA[] = "SELECT type, frequency FROM arduino.input_data_sendrate";


/*
struct Sender{
  char *type;
  unsigned int frequency;
  unsigned long timer;

  Sender() : type("default"), frequency(5000), timer(0){}
  Sender(char _type[],unsigned int _frequency, unsigned long _timer) : type(_type), frequency(_frequency), timer(_timer){}

};

Sender *senders;*/

char dataBuffer[100];

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
  Serial.println(F("Connecting with mysql server ..."));
  if(connection.connect(mysqlServerAddress, port, user, password)){
    Serial.println(F("Connected with mysql successfully."));
  }
  else{
    Serial.println(F("Connecion failed."));
    connection.close();
  }
}
/*
void initializeSenders(){
    MySQL_Cursor *currentCursor = new MySQL_Cursor(&connection);
    sprintf(query, EXTRACT_DATA);
    currentCursor->execute(query);
    column_names *cols = currentCursor->get_columns();
    row_values *row = NULL;
    int i = 0;
    do {
      row = currentCursor->get_next_row();
      if (row != NULL){
        Sender allSenders[cols->num_fields];
        allSenders[i] = Sender(row->values[0],(int)row->values[1],0);
        Serial.println(allSenders[i].type);
        senders = allSenders;
        i++;
      }
    } 
    while (row!=NULL);
    delete currentCursor;
}*/

void loop() {
        char query[128];
        sprintf(query, INSERT_INPUT_DATA, "test", getSensorData());  
        mysqlInsert(query); 
        
        /*if(Serial.available() < sizeof(dataBuffer)){
          Serial.readStringUntil('\n').toCharArray(dataBuffer, sizeof(dataBuffer));
          sprintf(query, INSERT_INPUT_DATA, "test", dataBuffer);  
          mysqlInsert(query); 
        }
        else{
          Serial.println("Data cant be sent");
        } */
    
    delay(1000);
}
      

void mysqlInsert(char query[]){
    MySQL_Cursor *currentCursor = new MySQL_Cursor(&connection);
    currentCursor->execute(query);
    delete currentCursor;
    Serial.println(query);
}

char *getSensorData(){

  StaticJsonBuffer<100> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();

  // Add values in the object
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root.set<long>("time", 1351824120);
  root["sensor"] = "gps";
  root["time"] = 1351824120;

  // Add a nested array.
  //
  // It's also possible to create the array separately and add it to the
  // JsonObject but it's less efficient.
  JsonArray& data = root.createNestedArray("data");
  data.add(double_with_n_digits(48.756080, 6));
  data.add(double_with_n_digits(2.302038, 6));
  root.prettyPrintTo(dataBuffer,sizeof(dataBuffer));
  delete &jsonBuffer;
  return dataBuffer;
}



