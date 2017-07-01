#define CHANGE_DELAY 1000 // How long a state stays
#define STATES 4 // How many combinations of colors
#define DIRECTIONS 2 // How many directions
#define COLORS 3 // How many colors
#define BLINK_REPEAT 5 // How many times to blink during repeat
#define BLINK_DELAY 100 // Wait in ms for emergency blinking
#define FIRST_PIN 5 // Pin of red light of 1st direction

// Pins
int LIGHTS[DIRECTIONS][COLORS];

// State - Direction - Color
int states[STATES][DIRECTIONS][COLORS] = 
{{{1,0,0},{0,0,1}},
 {{0,1,0},{0,1,0}},
 {{0,0,1},{1,0,0}},
 {{0,1,0},{0,1,0}}};

void setup() {
  int c = FIRST_PIN;
  //pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < DIRECTIONS; i++){
    for(int j = 0; j < COLORS; j++){
      LIGHTS[i][j] = c++;      
      pinMode(LIGHTS[i][j], OUTPUT);
    }
  }  
}

void state(int s){
  for(int i = 0; i < DIRECTIONS; i++){
    for(int j = 0; j < COLORS; j++){
      digitalWrite(LIGHTS[i][j],states[s][i][j]);
    }
  }
}
void transition(){
  for(int i = 0; i < STATES; i++){
    state(i);  
    delay(CHANGE_DELAY);
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

void loop() {  
  emergency();
  transition();
  transition();
}
