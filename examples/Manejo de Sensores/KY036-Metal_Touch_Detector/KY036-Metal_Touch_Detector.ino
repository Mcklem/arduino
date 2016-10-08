//LA PLACA DEBE CONECTARSE A TIERRA Y A LOS 5 VOLTIOS

int ledPin=11;//DIGITAL OUTPUT
int inputPin=7;//DIGITAL INPUT
int val;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(inputPin,INPUT);
}
void loop(){
  val = digitalRead(inputPin);
  if(val==HIGH){
    digitalWrite(ledPin,LOW);
  }
  else{
    digitalWrite(ledPin,HIGH);
  }
}
