
//obstacle_detection
#include "HCSR04.h"
#include "HCSR04_sensors.h"
Cican::Sensors sensors;


//check front
void ProcessFront() {
  long DistanceRight = sensors.distanceRight();
  delay(50);
  long DistanceFront = sensors.distanceFront();
  delay(50);
  long DistanceLeft = sensors.distanceLeft();
  delay(50);

  Serial.print("Distance R");Serial.print(DistanceRight);
  Serial.print(" F ");Serial.print(DistanceFront);
  Serial.print(" L ");Serial.println(DistanceLeft);
}



int nrTest;

//main logic
void setup() {
  Serial.begin(9600);
  Serial.println("Robot test!");
 
}

void loop() {

  ProcessFront();
  


}
