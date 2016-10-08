void initializeSD(){
  // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.html")) {
        Serial.println("ERROR - Can't find index.html file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.html file.");
}

boolean sendFileFromSD(EthernetClient client, File file){
  File sdFile = SD.open(file);   // open web page file
  if (sdFile) {
    while(sdFile.available()) {
      client.write(sdFile.read()); // send web page to client
    }
    sdFile.close();
    return true;
  }
  else{
    return false;                         
  }
}
