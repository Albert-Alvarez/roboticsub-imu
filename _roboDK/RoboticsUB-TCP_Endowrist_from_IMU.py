"""
********************************************************************************
RoboticsUB-TCP_Endowrist_from_IMU.py - Control based on a IMU.
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
********************************************************************************
"""

import serial
import time
import math

# RoboDK API: import the robolink library (bridge with RoboDK)
from robolink import *
# Robot toolbox: import the robodk library (robotics toolbox)
from robodk import *

# ------------------------------------------------------------------------------
# Connection
# ------------------------------------------------------------------------------

# Establish the connection on a specific port (COM3)
arduino = serial.Serial('COM3', 115200, timeout=1)

# Lets bring some time to the system to stablish the connetction
time.sleep(2)

# Establish a link with the simulator
RDK = Robolink()

# ------------------------------------------------------------------------------
# Simulator setup
# ------------------------------------------------------------------------------

# Retrieve all items (object in the robodk tree)
# Define the "robot" variable with our robot (UR5e)
robot = RDK.Item ('UR5e')

# Define the "home" variable with the initial position of our robot
home = RDK.Item ('Home')

# Define the "tcp" variable with the TCP of Endowrist needle
tcp_tool = RDK.Item('TCP_Endowrist')

# Performs a quick check to validate items defined
if robot.Valid():
    print('Robot selected: ' + robot.Name())
if tcp_tool.Valid():
    print('Tool selected: ' + tcp_tool.Name())
if home.Valid():
    print('Initial position: ' + home.Name())

# Matrixes that shows the Endowrist pose (TCP of Endowrist)
pose_tool = robot.Pose

# Tool frame with respect to Reference Frame
print ('Robot POSE is: ' + repr(pose_tool()))

# Tool frame with respect to Robot Flange
print ('Tool TCP pose is: ' + repr(tcp_tool.PoseTool()))

# ------------------------------------------------------------------------------
# Suture points
# ------------------------------------------------------------------------------

# Define the x,y,z value for first point (this values are the same for all
# suture points)
X = 0
Y = -58
Z = 320

# Print the defined coordinates (x,y,z)
print ('The coordinates (x,y,z) for the fist point are:')
print ('X is: ' + str(X))
print ('Y is: ' + str(Y))
print ('Z is: ' + str(Z) + '\n')

# ------------------------------------------------------------------------------
# Data comunication
# ------------------------------------------------------------------------------

try:
    while True:

        # Requesting data to Ardino (command A)
        arduino.write(b'A')

        # Storing received data
        roll_str = arduino.readline().strip()
        pitch_str = arduino.readline().strip()
        yaw_str = arduino.readline().strip()

        print(roll_str, pitch_str, yaw_str)

        # Convert variable values from string to float
        roll = float(roll_str)
        pitch = float(pitch_str)
        yaw = float(yaw_str)

        # Print the integer value of roll, pitch and yaw angles in degrees
        print('The R,P,Y angles (in degrees) from the MPU movements are: ')
        print('roll  (x-forward (north)): ' + str(roll))
        print('pitch (y-right (east): ' + str(pitch))
        print('yaw   (z-down (down)): ' + str(yaw) + '\n')

        # Convert from degrees to radians R,P,Y angles
        R = math.radians(roll)
        P = math.radians(pitch)
        W = math.radians(yaw)

        # Calculate the POSE matrix (UR)
    

        # Define the Endowrist TCP POSE in the first suture point (1st point)
        # by first point matrix POSE:
        tcp_tool_pose = tcp_tool.setPoseTool(pose_matrix)
        print ('Tool TCP pose in first point is: ' + repr(tcp_tool_pose.PoseTool()) + '\n')

except KeyboardInterrupt:
    print("Communication stopped.")
    pass

# ------------------------------------------------------------------------------
# Disconnect Arduino
# ------------------------------------------------------------------------------
print("Disconnecting Arduino...")
arduino.close()
