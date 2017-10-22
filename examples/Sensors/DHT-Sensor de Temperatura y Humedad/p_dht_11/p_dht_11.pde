
/*
* Test de Puertos utilizados
*/
import processing.serial.*;
Serial serial;
String portName;

PGraphics pg;

int rfs = 0;
int ldr_value = 0; // variable to store the value coming from the ldr sensor
int ultrasonic_value = 0; // variable to store the value coming from the ultrasonic sensor
int dht_temperature_value = 0;
int dht_humidity_value = 0;

void setup(){
  size(200,200);
  stroke(250);

  pg = createGraphics(100, 100);
  portName = Serial.list()[0];
  serial = new Serial(this, portName, 9600);
}

void draw(){
  
  readFromSerial();
  background(0);   // Clear the screen with a black background
  line(0, 10 , 10, 10+ ldr_value);
  line(10, 0 , 100, 0);
  line(0, 10 , 0, 100);
  /*pg.line(20, 10 , 20, 10+ultrasonic_value);
  pg.line(30, 10 , 30, 10+dht_temperature_value);
  pg.line(40, 10 , 40, 10+dht_humidity_value);*/

}

void readFromSerial(){
  
  if ( serial.available() > 0) 
  { 

    ldr_value = (int) serial.read();
  } 
}