#ifndef __PAPIDController__
#define __PAPIDController__

#include <stdint.h>

class PAPIDController {
    const float Kp;
    const float Ki;
    const float Kd;
    float integrationValue = 0;
    float integrationLimit;
    uint16_t lastTime = 0;
    float lastError = 0;
    
public:
    PAPIDController(float Kp, float Ki, float Kd);
    float next(float error);
};

#endif
