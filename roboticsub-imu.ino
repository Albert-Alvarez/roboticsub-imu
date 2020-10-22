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

IMU imu;

float * rpy; // Pointer to read RPY
char instruction = 0; // For incoming serial data

void setup() 
{

  Serial.begin(115200);
  
  imu.Install();

  attachInterrupt(digitalPinToInterrupt(8), imuISR, RISING);
  
}

void loop() 
{

  if (Serial.available() > 0) {
    
    // read the incoming byte:
    instruction = Serial.read();

    switch(instruction){
      case 'A':

        rpy = imu.GetRPY();
              
        Serial.println(String(rpy[0], 4));
        Serial.println(String(rpy[1], 4));
        Serial.println(String(rpy[2], 4));

        break;
        
      default:
        break;
    }

    instruction = NULL;
    
  }  
}

void imuISR(void) {
  
  imu.ReadSensor();

}
