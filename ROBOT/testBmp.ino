
//locomotion
#include "L298N.h"
#include "L298N_motor_driver.h"
Cican::Motors motors(255);

//obstacle_detection
#define EchoRight 26
#define TrigRight 27
#define EchoFront 24
#define TrigFront 25
#define EchoLeft 22
#define TrigLeft 23

#include "HCSR04.h"
//#include "HCSR04_sensors.h"
//Cican::Sensors sensors;
HCSR04 SensorRight(EchoRight, TrigRight);
HCSR04 SensorFront(EchoFront, TrigFront);
HCSR04 SensorLeft(EchoLeft, TrigLeft);

//volatile int TurnDistanceFront = 40;
//volatile int TurnDistanceRight = 40;
//volatile int TurnDistanceLeft = 40;
//volatile int MaxDistanceRight = 20;
//volatile int MaxDistanceFront = 20;
//volatile int MaxDistanceLeft = 20;

int TurnDistance = 40;
int MaxDistance = 20;

#define Fw 1
#define Bw 2
#define FR 3
#define FL 4
#define BR 5
#define BL 6
#define ST 10


//check distance
int ProcessDistance(long DistanceRight, long DistanceFront, long DistanceLeft, int poz) {
  int nrOp = ST;
  long distance;
  switch (poz) {
    case 1: {
      distance = DistanceRight; 
      break;
    }
	
	case 2: {
      distance = DistanceFront; 
      break;
    }
	
	case 3: {
      distance = DistanceLeft; 
      break;
    }
  }	
  
  if ((distance <= TurnDistance) && (DistanceFront >= MaxDistance)) {
    if ((DistanceRight <= DistanceLeft) && (DistanceRight >= MaxDistance)) {
      nrOp = FL;
    }
    else if ((DistanceRight <= DistanceLeft) && (DistanceRight < MaxDistance)) {
      nrOp = BL;
    }
    else if ((DistanceLeft <= DistanceRight ) && (DistanceLeft >= MaxDistance)) {
      nrOp = FR;
    }
    else if ((DistanceLeft <= DistanceRight ) && (DistanceLeft < MaxDistance)) {
      nrOp = BR;
    }
  }
  else if (distance < MaxDistance) {
    if ((DistanceRight <= DistanceLeft) && (DistanceRight < MaxDistance)) {
      nrOp = BL;
    }
    else if ((DistanceLeft <= DistanceRight ) && (DistanceLeft < MaxDistance)) {
      nrOp = BR;
    }
  }
  else {
    nrOp = Fw;
  }

  Serial.print("Op "); Serial.println(nrOp);
  return nrOp;
}


int nrTest, nrTestCrt, Bumper;
long dRight, dFront, dLeft;
boolean start, collision;

//main logic
void setup() {
  Serial.begin(9600);
  Serial.println("Robot test!");
  
  //front bumper
  pinMode(63, INPUT_PULLUP);
  
  start = true;
  collision = false;
  nrTest = 1;  
}

void loop() {

//  Serial.println("ProcessFront");
  Bumper = digitalRead(63);
  dRight = SensorRight.distance();
  delay(50);
  dFront = SensorFront.distance();
  delay(50);
  dLeft = SensorLeft.distance();
  delay(50);
  
  nrTest = 1; 
  nrTestCrt = 1; 
  
  if (Bumper == HIGH) {
    if (dRight <= TurnDistance) {
	  collision = true;
      nrTestCrt = ProcessDistance(dRight, dFront, dLeft, 1);
	}  
    else if (dFront <= TurnDistance) {
	  collision = true;
      nrTestCrt = ProcessDistance(dRight, dFront, dLeft, 2);
	}  
    else if (dLeft <= TurnDistance) {
	  collision = true;
      nrTestCrt = ProcessDistance(dRight, dFront, dLeft, 3);
	}
  }
  else {
    collision = true;
    nrTestCrt = 6;
	
	Serial.println("bumper LOW");
  }
  
  Serial.print("nr test crt ");Serial.println(nrTestCrt);
  
  if (!motors.canMoving() || collision) {
    motors.reset();
    nrTest = nrTestCrt; 
	start = false;
	collision = false;

	Serial.print("modific test  ");Serial.println(nrTestCrt);
  }
  
  Serial.print("nr test actual ");Serial.println(nrTest);
  

  switch (nrTest) {
    case 1: {
      motors.MoveForward(255); 

//      motors.MoveSpiral(30000, 255); 
      break;
    }
	
    case 2: {
	  motors.MoveBackward(100);
      break;
    }
	
	case 3: {
      motors.MoveForwardRight(200, 100);
      break;
    }
	  
	case 4: {
	  motors.MoveForwardLeft(200, 100);
      break;
    }

    case 5: {
      motors.MoveBackwardRight(200, 100);
      break;
    }

    case 6: {
      motors.MoveBackwardLeft(200, 100);
      break;
    }

    case 10: {
      motors.MoveStop();
      break;
    }
	
 
}


}
