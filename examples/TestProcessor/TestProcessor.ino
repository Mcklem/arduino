//This program can test processor calculation capacity

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
long i = 0;
bool printed = false;
void loop() {
  
  if(millis()/1000>10){
    if(!printed){
      Serial.println(i);
      printed = true;
    }
  }
  else{
    i++;
  }
  
}
