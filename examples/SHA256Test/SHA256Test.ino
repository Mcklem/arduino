#include <Crypto.h>
#include <SHA256.h>
#include <string.h>

SHA256 sha256;

byte buffer[32];

byte customHash[32] = {//data:abcdefghijklmnopqrstuvwxyz key:990099
0x5d,
0xae,
0x15,
0xae,
0x30,
0xf7,
0x2b,
0x0d,
0xf1,
0xc6,
0x0e,
0x40,
0xbe,
0xa4,
0xd6,
0xf4,
0x59,
0x9f,
0x53,
0x35,
0xd1,
0x2a,
0xd9,
0x1d,
0x69,
0xfd,
0xf0,
0xb6,
0x74,
0x24,
0x63,
0x21};

char header[7];
char body[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
#define digit "%d"

void generateHashHMAC(Hash *hash)
{
    int a = random(0,999999);
    
    //dtostrf(a, 6, 0, chars);//High consumption -1200h/s aprox

    sprintf(header, digit, a);//char[] %s, int %d //Medium consumption -500h/s
    
    hash->resetHMAC(header,sizeof(header));
    hash->update(body, 26);
    hash->finalizeHMAC(header,sizeof(header),buffer, hash->hashSize());

    if(memcmp(buffer, customHash, sizeof(buffer))==0){
      Serial.print("Got it! at ");
      Serial.print(millis()/1000);
      Serial.print("s Key: ");
      for (int posn = 0; posn < sizeof(buffer); ++posn){
        Serial.print(buffer[posn],HEX);
      }
      Serial.println();
    }

}

void setup()
{
    Serial.begin(115200);
    randomSeed(analogRead(0));
}

void loop()
{
  serialCommands();
  mine();
}

void serialCommands(){
  if (Serial.available()){
    
    String command = Serial.readStringUntil('\r\n');
    
    char buf[256];
    command.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *comm;
    while ((comm = strtok_r(p, " ", &p)) != NULL)//SEPARATE BY SPACES
    {
      char *strA = strtok_r(comm, ":", &comm);//SEPARATE BY COLON
      char *strB = strtok_r(comm, ":", &comm);
      if(strA!=NULL&&strB!=NULL){
        Serial.print(strA);
        Serial.println(strB);
        if(strA[0]=='H'){
          if(strlen(strB)!=64){ 
            Serial.println(F("SHA256 (64 characters) was not found for command H"));
            return;
          }
          
          Serial.print("New hash: ");
          for(int i = 0; i<32;i++){//HASH REPLACEMENT
            customHash[i] = ascii2HexToByte((char)strB[i*2], (char)strB[i*2+1]);
            Serial.print(customHash[i],HEX);
          }
          Serial.println();
          
        }
      }
      else{
        Serial.println("error");
      }
    }
    command = ""; 
  }
}

unsigned short charToHexDigit(char c)
{
  if (c>=97){
      return (c - 97 + 10);//c - 'a' (ASCII VALUE) + decimal value of HEX 'a' 
  }
  else if (c >= 65 && c <97){
      return (c - 65 + 10);//c - 'A' (ASCII VALUE) + decimal value of HEX 'A' 
  }
  else return (c - 48);//c - '0' (ASCII VALUE)
}

unsigned char ascii2HexToByte(char a, char b)
{
    return charToHexDigit(a)*16 + charToHexDigit(b);
}


unsigned long timer;
int hashes;
void mine(){
    if(micros()>=timer){
        timer = micros() + 1000000;
        Serial.print(hashes);
        Serial.println(" H/s");
        /*for (int posn = 0; posn < sizeof(buffer); ++posn){
          Serial.print(buffer[posn],HEX);
        }*/
        Serial.println();
        hashes = 0;
  
        //if(millis()>5000) softwareReset();
    }
    else{
      generateHashHMAC(&sha256);
      hashes++;
    }
}
/*
void softwareReset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");  
}  */
