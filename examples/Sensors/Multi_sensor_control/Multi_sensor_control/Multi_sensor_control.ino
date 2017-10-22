#include <Ultrasonic.h>
#include <dht.h>
dht DHT;


#define LDR_PIN A0 // select the input pin for ldr
#define US_TG_PIN 9
#define US_E_PIN 8
#define DHT_PIN 7
#define LED_R_PIN 6
#define LED_G_PIN 5
#define LED_B_PIN 3

Ultrasonic ultrasonic(US_TG_PIN, US_E_PIN); // (Trig PIN,Echo PIN)

unsigned int ldr_update_freq = 100;
unsigned int ultrasonic_update_freq = 100;
unsigned int dht_update_freq = 1000;
unsigned int serial_write_freq = 100;

int ldr_value = 0; // variable to store the value coming from the ldr sensor
int ultrasonic_value = 0; // variable to store the value coming from the ultrasonic sensor
int dht_value = 0; //
int led_value_r = 0;
int led_value_g = 0;
int led_value_b = 0;

unsigned long ldrTimer = 0;
unsigned long ultrasonicTimer = 0;
unsigned long dhtTimer = 0;
unsigned long serial_write_timer = 0;

void setup() {
  Serial.begin(9600); //sets serial port for communication
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void loop() {
  setLDRValue();
  setUltrasonicValue();
  setDHTValue();
  setLEDState();
  String str = readFromSerial();
  if(str!="") Serial.println(str);
  command(str);
  writeToSerial();
}

void setLDRValue(){
  if(millis()>=ldrTimer){
    ldr_value = analogRead(LDR_PIN); // read the value from the sensor
    ldrTimer = millis() + ldr_update_freq;
  }
}

void setUltrasonicValue()
{
  if(millis()>=ultrasonicTimer){
    ultrasonic_value = ultrasonic.Ranging(CM);
    ultrasonicTimer = millis() + ultrasonic_update_freq;
  }
}

void setDHTValue()
{
  if(millis()>dhtTimer){
    dht_value = DHT.read11(DHT_PIN);
    dhtTimer = millis() + dht_update_freq;
  }
}

void writeToSerial(){
  if(millis()>=serial_write_timer){
    Serial.println((String)ldr_value + "," + ultrasonic_value + "," + DHT.temperature + "," + DHT.humidity + "," + freeRam() + "," + led_value_r + "," + led_value_g + "," + led_value_b);//LA APLICACION OBTENDRÁ LOS DATOS SEPARANDO POR COMAS
    serial_write_timer = millis() + serial_write_freq;
  }
}

String readFromSerial(){//THIS LET READ TRUE DATA WITHOUT ASCII Characters 0 4 (null + EOT) and 32 47 114 (space + / + r) at the end
  String str = "";
  if(Serial.available()>0){
     str = Serial.readStringUntil(10);
     str = str.substring(2, str.length()-3);
  }
  return str;
}

void setLEDState(){
  analogWrite(LED_R_PIN, led_value_r);
  analogWrite(LED_G_PIN, led_value_g);
  analogWrite(LED_B_PIN, led_value_b);
}

void command(String s){

  int v = parseInt(s);
  String f = (String) v;
  String w = s.substring(0, s.length() - f.length());
  
  if(w=="LR"){
    led_value_r = v;
  }
  else if(w=="LG"){
    led_value_g = v;
  }
  else if(w=="LB"){
    led_value_b = v;
  }
  else if(w=="ldr_update_freq"){
    ldr_update_freq = v;
  }
  else if(w=="ultrasonic_update_freq"){
    ultrasonic_update_freq = v;
  }
  else if(w=="dht_update_freq"){
    dht_update_freq = v;
  }
  else if(w=="serial_write_freq"){
    serial_write_freq = v;
  }
}

int parseInt(String s){//RETORNA SOLO LOS CARACTERES DE TIPO INT
    String r = "";
    for(int i = 0;i<s.length();i++){
      if (isDigit(s[i])) {
        r += (char)s[i];
      }
    }
    return r.toInt();
}

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

