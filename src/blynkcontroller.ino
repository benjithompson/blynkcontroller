//Tilt sensor activates state change and powers on
//D1 Mini

//Settings   
#define tilt_wait   500
#define tiltPin 2
#define powerPin 12

//Status Variables   
uint8_t prev_state;
long last_msg = 0;
int tilt_state;
bool msg_sent = false;
bool send_shutdown = false;

void setup() {
  
  Serial.begin(9600);

  //Tilt
  pinMode(tiltPin, INPUT);
  pinMode(powerPin, OUTPUT);
}

void loop() {

  //Wait for tilt status check
  long now = millis();
  if((now - last_msg) > tilt_wait){
    tilt_state = digitalRead(tiltPin);
    last_msg = millis();

    //check for new tilt status
    if (tilt_state != prev_state) {
      
      //Serial
      if(tilt_state){
        Serial.print("Door Open.");
        digitalWrite(powerPin, HIGH);
      }else{

        Serial.println("Door Closed. Shutting down circuit...");
        delay(2000);
        digitalWrite(powerPin, LOW);
      }
      prev_state = tilt_state;
    }
  }
}
