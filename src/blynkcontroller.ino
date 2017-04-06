//Tilt sensor activates state change and powers on
//D1 Mini

//Settings
#define tilt_wait   1000
#define in_pin 2
#define out_pin 3
#define powerPin 4

//Status Variables
volatile long last_msg = 0;
volatile bool mail_empty = true;
// bool msg_sent = false;
// bool send_shutdown = false;

void in_isr(){
  //Wait for tilt status check
  long now = millis();

  //wiats for tilt_wait
  if((now - last_msg) > tilt_wait && mail_empty == true){
    last_msg = millis();
    Serial.println("New Mail!");
    digitalWrite(powerPin, LOW);
    mail_empty = false;
  }

}

void out_isr(){
  //Wait for tilt status check
  long now = millis();

  //waits for tiltwait
  if((now - last_msg) > tilt_wait && mail_empty == false){
    last_msg = millis();

    Serial.println("Obtained.");
    digitalWrite(powerPin, LOW);

    mail_empty = true;
  }
}


void setup() {

  Serial.begin(9600);

  //Tilt
  pinMode(in_pin, INPUT_PULLUP);
  pinMode(out_pin, INPUT_PULLUP);
  pinMode(powerPin, OUTPUT);

  //Interupt
  attachInterrupt(digitalPinToInterrupt(in_pin), in_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(out_pin), out_isr, RISING);
  
}

void loop() {

}
