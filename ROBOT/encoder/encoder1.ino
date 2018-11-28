//locomotion
#include "L298N.h"
#include "L298N_motor_driver.h"
Cican::Motors motors(255);

int encoderRC1 = 3;
int encoderRC2 = 2;

int pulsesChanged = 0;
int pulses;

#define total 245                        //x1 pulses per rotation.
#define motorSpeed 180 

void setup(){
  Serial.begin(9600);
  
  pinMode(encoderRC1, INPUT);
  pinMode(encoderRC2, INPUT);


  attachInterrupt(digitalPinToInterrupt(encoderRC2), count, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);


}//setup

void loop(){
 if (pulses == total) {
    motors.MoveStop();
  }
  else {
    if (pulses > total) {
      motors.MoveBackward(100);    }
    else if (pulses < total) {
      motors.MoveForward(255); 
    }
  }
  
  if (pulsesChanged != 0) {
    pulsesChanged = 0;
    Serial.println(pulses);
  }
}

void count() {
  pulses++;
  pulsesChanged = 1;
}
