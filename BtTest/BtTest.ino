#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); 

int ledpin = 13;
int password = 1234;

void setup() {
  pinMode(ledpin, OUTPUT);
  mySerial.begin(38400);
}

void loop() {  
  int btInput = 0;
  if( mySerial.available() ){
    btInput = mySerial.parseInt();
  }
  if( btInput == password )              
  {
    digitalWrite(ledpin, HIGH);  
  } else { 
    digitalWrite(ledpin, LOW);  
  }
  delay(1000);
}
