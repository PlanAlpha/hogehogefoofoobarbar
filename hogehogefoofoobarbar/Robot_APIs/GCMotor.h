#ifndef __GCMotor__
#define __GCMotor__

#include "../Core_APIs/DigitalOut.h"
#include "../Core_APIs/PwmOut.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
class GCMotor {
public:
    static constexpr int numOfSteps = 5;
    
private:
    DigitalOut digital1;
    DigitalOut digital2;
    PwmOut  analog;
    int16_t currentSpeed;
    int16_t steps[numOfSteps];
    int16_t lastSpecifiedPower;
    bool shouldHold;
    bool shouldFree;
    int16_t *stepsPoint;
    const int16_t *stepsTerminalPoint;
    
public:
    GCMotor(uint8_t dig1, uint8_t dig2, uint8_t ana);
    void forward(int16_t power);
    void hold(void);
    void free(void);
    void holdImmediately();
    void freeImmediately();
    void setPower(int16_t power);
    int fixPower;
    int16_t getCurrentSpeed();
};
#pragma GCC diagnostic pop

#endif
