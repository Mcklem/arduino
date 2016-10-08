//PERMITE CONOCER LA DIRECCIÓN DEL CAMPO MAGNETICO


int Led=11;
int SENSOR=A0;
float val;

void setup(){
  pinMode(Led,OUTPUT);
  pinMode (SENSOR,INPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(SENSOR);
  Serial.println(val);
  delay(300);
}

