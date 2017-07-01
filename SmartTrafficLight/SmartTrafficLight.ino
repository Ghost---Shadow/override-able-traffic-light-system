#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); 

#define CHANGE_DELAY 3000 // How long a state stays
#define STATES 4 // How many combinations of colors
#define DIRECTIONS 2 // How many directions
#define COLORS 3 // How many colors
#define BLINK_REPEAT 5 // How many times to blink during repeat
#define BLINK_DELAY 100 // Wait in ms for emergency blinking
#define FIRST_PIN 5 // Pin of red light of 1st direction
#define BAUD 38400 // Baud for Serial coms

// Pins
int LIGHTS[DIRECTIONS][COLORS];

// State - Direction - Color
int states[STATES][DIRECTIONS][COLORS] = 
{{{1,0,0},{0,0,1}},
 {{0,1,0},{0,1,0}},
 {{0,0,1},{1,0,0}},
 {{0,1,0},{0,1,0}}};

void setState(int s){
  for(int i = 0; i < DIRECTIONS; i++){
    for(int j = 0; j < COLORS; j++){
      digitalWrite(LIGHTS[i][j],states[s][i][j]);
    }
  }
}
void emergency(){
  // Reset
  for(int i = 0; i < DIRECTIONS; i++){
    for(int j = 0; j < COLORS; j++){
      digitalWrite(LIGHTS[i][j],LOW);
    }
  }
  
  // Blink Yellow
  for(int k = 0; k < BLINK_REPEAT; k++){
    for(int i = 0; i < DIRECTIONS; i++)
      digitalWrite(LIGHTS[i][1],HIGH);
    delay(BLINK_DELAY);
    
    for(int i = 0; i < DIRECTIONS; i++)
      digitalWrite(LIGHTS[i][1],LOW);
    delay(BLINK_DELAY);
  }
}

int state;
unsigned long last;
int password = 1234;

void setup() {  
  mySerial.begin(BAUD);
  Serial.begin(9600); // DEbug
  
  pinMode(LED_BUILTIN, OUTPUT);
  int c = FIRST_PIN;
  state = 0;
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 3; j++){
      LIGHTS[i][j] = c++;
      pinMode(LIGHTS[i][j], OUTPUT);
    }
  }  
  last = millis();
}

void loop() {  
  digitalWrite(LED_BUILTIN, LOW);
  int btInput = 0;  
  if(last < 0)
    last = millis();
  if(millis() - last >= CHANGE_DELAY){
    Serial.print(millis());
    Serial.println(last);
    last = millis();
    state = (state + 1) % STATES;    
  }
  
  if( mySerial.available() ){
    btInput = mySerial.parseInt(); 
    mySerial.flush();
  } 
  
  if( btInput == password ){
    Serial.println("Change");
    digitalWrite(LED_BUILTIN, HIGH);  
    emergency();
    state = (state + 2) % STATES;
    last = millis();
  } 
  
  setState(state);
  delay(1); // Prevent over heating
}
