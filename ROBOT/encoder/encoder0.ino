//locomotion
#include "L298N.h"
#include "L298N_motor_driver.h"
Cican::Motors motors(255);

int encoderRC1 = 3;
int encoderRC2 = 2;

int pulsesChanged = 0;
int pulses = 0;

#define total 2800                      //x1 pulses per rotation.
#define motorSpeed 50 

void setup(){
  Serial.begin(9600);
  
  pinMode(encoderRC1, INPUT);
  pinMode(encoderRC2, INPUT);


  attachInterrupt(digitalPinToInterrupt(encoderRC2), A_CHANGE, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);


}//setup

void loop(){
 if (pulses == total) {
    motors.MoveStop();
  }
  else {
    if (pulses > total) {
      motors.MoveBackward(50);    }
    else if (pulses < total) {
      motors.MoveForward(50); 
    }
  }
  
  if (pulsesChanged != 0) {
    pulsesChanged = 0;
    Serial.println(pulses);
  }
}

void A_CHANGE(){                                  //Function that to read the pulses in x1.
  if( digitalRead(encoderRC2) == 0 ) {
    if ( digitalRead(encoderRC1) == 0 ) {
      // A fell, B is low
      pulses--; // moving reverse
    } else {
      // A rose, B is low
      pulses++; // moving forward
    }
  }
  pulsesChanged = 1;
}
