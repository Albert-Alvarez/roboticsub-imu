#include "src/RoboticsUB.h"

IMU imu;

void setup() 
{

  Serial.begin(115200);
  
  imu.Install();

  attachInterrupt(digitalPinToInterrupt(8), imuISR, RISING);
  
}

void loop() 
{
  
}

void imuISR(void) {

  float * q;
  
  q = imu.GetQuaternion();

  Serial.println(
    "Q: " +
    String(q[0], 4) + ", " +
    String(q[1], 4) + ", " +
    String(q[2], 4) + ", " +
    String(q[3], 4)
  );
}
