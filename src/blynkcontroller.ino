//Tilt sensor activates state change and powers on
//D1 Mini

//TODO: enable wifi for a given amount of time (turn on D4) to allow
//      wifi to push change "New Mail", or "Mailbox Empty"

#include <SimpleTimer.h>

//Settings
#define tilt_wait   1000 //1s
#define wifi_wait  10000 //10s
#define sleep_wait  1000 //1s
#define in_pin         2
#define out_pin        3
#define esp_on_pin    12

//Status Variables
volatile long last_msg =      0;
volatile bool mail_empty = true;

SimpleTimer timer;


void wifiOnInterval(){
  Serial.println("Turning on esp wifi pin for 10 secs");
  digitalWrite(esp_on_pin, HIGH);
  timer.setTimeout(wifi_wait, wifiShutoff);
  
}

void wifiShutoff(){
  Serial.println("esp shutoff.");
  digitalWrite(esp_on_pin, LOW);
}

void deepSleep(){
  
}

void in_isr(){
  //Wait for tilt status check
  long now = millis();

  //wiats for tilt_wait
  if((now - last_msg) > tilt_wait && mail_empty == true){
    last_msg = millis();
    Serial.println("New Mail!");
    mail_empty = false;
    wifiOnInterval();
    
  }

}

void out_isr(){
  //Wait for tilt status check
  long now = millis();

  //waits for tiltwait
  if((now - last_msg) > tilt_wait && mail_empty == false){
    last_msg = millis();
    Serial.println("Obtained.");
    mail_empty = true;
    wifiOnInterval();
  }
}


void setup() {
  
  Serial.begin(9600);
  
  //Tilt
  pinMode(in_pin, INPUT_PULLUP);
  pinMode(out_pin, INPUT_PULLUP);
  pinMode(esp_on_pin, OUTPUT);

  //Interupt
  attachInterrupt(digitalPinToInterrupt(in_pin), in_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(out_pin), out_isr, RISING);

  //timer
  timer.setInterval(sleep_wait, deepSleep());
  
}

void loop() {
  timer.run();
}
