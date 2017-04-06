//Tilt sensor activates state change and powers on
//D1 Mini

//Settings
#define tilt_wait   1000
#define tiltPin 2
#define powerPin 4

//Status Variables
volatile long last_msg = 0;
volatile int tilt_state;
bool msg_sent = false;
bool send_shutdown = false;

void door_close_isr(){
  //Wait for tilt status check
  long now = millis();
  if((now - last_msg) > tilt_wait){
    
    last_msg = millis();
    Serial.println(digitalRead(tiltPin));
    
    Serial.println("Door Closed.");
    digitalWrite(powerPin, LOW);
  }
}

void door_open_isr(){
  //Wait for tilt status check
  long now = millis();
  if((now - last_msg) > tilt_wait){
    
    last_msg = millis();
    Serial.println(digitalRead(tiltPin));
    Serial.println("Door Opened.");
    digitalWrite(powerPin, LOW);
  }
}


void setup() {

  Serial.begin(9600);

  //Tilt
  pinMode(tiltPin, INPUT_PULLUP);
  pinMode(powerPin, OUTPUT);

  //Interupt
  attachInterrupt(digitalPinToInterrupt(tiltPin), door_open_isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(tiltPin), door_close_isr, RISING);

}

void loop() {

}
