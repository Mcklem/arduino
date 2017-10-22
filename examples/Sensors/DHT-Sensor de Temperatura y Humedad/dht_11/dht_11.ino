
#include <dht.h>

dht DHT;

#define DHT11_PIN 8

unsigned long timer;

void setup(){
  Serial.begin(9600);
}

void loop()
{
  if(millis()>timer){
    int chk = DHT.read11(DHT11_PIN);
    /*Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    */
      Serial.println(DHT.temperature);
      Serial.println(DHT.humidity);
    
    //Serial.write(DHT.humidity);
    timer = millis() + 1000l;
  }
}

