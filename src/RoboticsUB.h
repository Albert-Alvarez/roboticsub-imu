#ifndef ROBOTICS_UB
#define ROBOTICS_UB

#include "SparkFunMPU9250-DMP.h"

class IMU: public MPU9250_DMP {
    public:
        IMU();
        void Install(void);
        float * GetQuaternion(void);
};

#endif