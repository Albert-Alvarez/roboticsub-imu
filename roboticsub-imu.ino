/******************************************************************************
roboticsub-imu.ino - MPU Arduino library example
Copyright (C) 2020  Albert Álvarez-Carulla
Repository: https://github.com/Albert-Alvarez/roboticsub-imu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
******************************************************************************/

#include "src/RoboticsUB.h"
#include <Servo.h>

IMU imu;
Servo servo1;

float * rpw; // Pointer to read RPW
char instruction = 0; // For incoming serial data
int Pin_R1 = A0; // Analogic pin used by R1 (Servo1)
float R1 = 4.7; // Resistance value
float torque = 0; // Indicated as current (ampere)
float motor_angle = 0; // Motor angle

void setup() 
{

  Serial.begin(115200);
  
  imu.Install();
  servo1.attach(9);

  attachInterrupt(digitalPinToInterrupt(8), imuISR, RISING);
  
}

void loop() 
{

  if (Serial.available() > 0) {
    
    // read the incoming byte:
    instruction = Serial.read();

    switch(instruction){
      case 'A':        
              
        Serial.println(String(rpw[0], 4));
        Serial.println(String(rpw[1], 4));
        Serial.println(String(rpw[2], 4));    
        Serial.println(String(torque, 4));    

        break;
        
      default:
        break;
    }

    instruction = NULL;
    
  }  

  rpw = imu.GetRPW();
  
  // Angle range from 0 to 180 degrees
  
  if (rpw[2] <= 180 && rpw[2] >= 0) {
    motor_angle = rpw[2]; 
  }
  
  servo1.write(motor_angle);
  
  torque = analogRead(Pin_R1) * (3.3 / 1023.0) / R1;
  
}

void imuISR(void) {
  
  imu.ReadSensor();

}
