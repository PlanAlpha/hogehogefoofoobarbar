#ifndef __GCMotor__
#define __GCMotor__

#include "../Core_APIs/PwmOut.h"

class GCMotor {
    PwmOut pin1;
    PwmOut pin2;
    
public:
    GCMotor(uint8_t pin1, uint8_t pin2);
    void forward(int32_t power);
    void forward(float power);
    void forward(double power) {
        forward(static_cast<float>(power));
    }
    void free();
};

#endif
