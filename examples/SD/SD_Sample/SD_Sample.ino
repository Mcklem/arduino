#include <SD.h>

//chip select pin for the MicroSD Card Adapter
#define cs 4 

String path = "Readme.txt";

void setup() {
  Serial.begin(9600); // start serial connection to print out debug messages and data
  pinMode(4, OUTPUT); // chip select pin must be set to OUTPUT mode
  
  if (!SD.begin(4)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }
  
}

File file;

void loop() {
  if(SD.exists(path)) {
    file = SD.open(path, FILE_WRITE);
    long t = millis()/1000;
    writeLine(file,(String)t);
    
    file = SD.open(path, FILE_READ);
    Serial.println(readAllLines(file));
  }
  else{
    return;
  }
    
  delay(5000); // wait for 5000ms
}

bool removeFile(String file){
  if (SD.exists(file)) {
    if (SD.remove(file)) {
      Serial.println("Successfully removed file.");
    } 
    else {
      Serial.println("Could not removed file.");
    }
  }
  else{
    Serial.println("File not exists.");
  }
}

String readAllLines(File file){

  if(!file.isDirectory()){
    String str = "";
    if (file) {
      char character;
      while ((character = file.read()) != -1) { // this while loop reads data stored in "file.txt" and prints it to serial monitor
        str += character;
      }
      file.close();
    } 
    else {
      Serial.println("Could not open file (reading).");
    }
    return str;
  }
}

void writeLine(File file, String line){
  if (file) {
    file.println(line);
    file.close();
  }
  else {
    Serial.println("Could not open file (reading).");
  }
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

