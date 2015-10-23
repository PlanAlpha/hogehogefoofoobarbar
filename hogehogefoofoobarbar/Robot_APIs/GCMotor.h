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
    int32_t currentSpeed;
    int32_t steps[numOfSteps];
    int32_t lastSpecifiedPower;
    bool shouldHold;
    bool shouldFree;
    int32_t *stepsPoint;
    const int32_t *stepsTerminalPoint;
    
public:
    GCMotor(uint8_t dig1, uint8_t dig2, uint8_t ana);
    void forward(int32_t power);
    void forward(float power);
	void forward(double power) {
		forward(static_cast<float>(power));
	}
    void hold(void);
    void free(void);
    void holdImmediately();
    void freeImmediately();
    void setPower(int32_t power);
    int fixPower;
    int32_t getCurrentSpeed();
};
#pragma GCC diagnostic pop

#endif
