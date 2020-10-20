#include "RoboticsUB.h"

IMU::IMU() {}

void IMU::Install(void) {

    Serial.begin(115200);

    if (begin() != INV_SUCCESS) {
        while (1) {
            delay(5000);
        }
    }

    dmpBegin(
        DMP_FEATURE_6X_LP_QUAT |    // Enable 6-axis quat
        DMP_FEATURE_GYRO_CAL,       // Use gyro calibration
        10                          // Set DMP FIFO rate to 10 Hz
    );                       
    
    // DMP_FEATURE_LP_QUAT can also be used. It uses the 
    // accelerometer in low-power mode to estimate quat's.
    // DMP_FEATURE_LP_QUAT and 6X_LP_QUAT are mutually exclusive

    return;
}

float * IMU::GetQuaternion(void) {

    static float q[4];

    if (fifoAvailable()) {
        if (dmpUpdateFifo() == INV_SUCCESS) {
    
            q[0] = calcQuat(qw);
            q[1] = calcQuat(qx);
            q[2] = calcQuat(qy);
            q[3] = calcQuat(qz);

        }
    }
    
    return q;
}