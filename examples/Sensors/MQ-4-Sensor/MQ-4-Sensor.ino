/*
 * This program let find variations over MQ-4 sensor, it will take init value from first read as control point (limit)
 */

#define AOUTpin A0//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
#define ledPin 13//the anode of the LED connects to digital pin D13 of the arduino

int limit = 0;
int value = 0;

void setup() {
  Serial.begin(9600);//sets the baud rate
  pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

void loop()
{
  value = analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
  if(limit==0) {
    limit = value;//Sets first value as limit
    Serial.println("Limit is " + String(limit) + " now");
  }
  Serial.println("CH4 value: " + String(value));//prints the CH4 value
  delay(100);
  if (value>limit){
    digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
  }
  else{
    digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
  }
}

