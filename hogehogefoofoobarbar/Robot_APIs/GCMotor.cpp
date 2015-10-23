#include "GCMotor.h"
#include <stdlib.h>
#include <math.h>

#define radians(d) (d * M_PI / 180)

GCMotor::GCMotor(uint8_t dig1, uint8_t dig2, uint8_t ana) : digital1(dig1), digital2(dig2), analog(ana), currentSpeed(0), lastSpecifiedPower(0), shouldHold(false), shouldFree(false), stepsPoint(steps), stepsTerminalPoint(steps + numOfSteps - 1), fixPower(0)
{
    for (int i = 0; i < numOfSteps; i++) {
        steps[i] = 0;
    }
    freeImmediately();
}

#define ENABLE_SIN

void GCMotor::forward(int16_t power)
{
    if (lastSpecifiedPower == power) {
        if (stepsPoint != stepsTerminalPoint)
            currentSpeed = *++stepsPoint;
    } else {
        stepsPoint = const_cast<int16_t *>(stepsTerminalPoint);
#ifdef ENABLE_SIN
#undef round
        int16_t a = abs(currentSpeed - power) / 2;
        int16_t b = (currentSpeed + power) / 2;
        int16_t step = 180 / numOfSteps;
        int16_t x = 180 - step;
        int16_t p = currentSpeed < power ? 90 : -90;
        *stepsPoint = power;
        while (stepsPoint-- != steps) {
            *stepsPoint = static_cast<int16_t>(round(a * sin(radians(x - p)) + b));
            x -= step;
        }
#else
        int16_t step = (power - currentSpeed) / numOfSteps;
        int16_t current = power;
        *stepsPoint = power;
        while (stepsPoint-- != steps) {
            *stepsPoint = (current -= step);
        }
#endif
        lastSpecifiedPower = power;
        currentSpeed = *++stepsPoint;
    }
    setPower(currentSpeed);
}

#ifdef ENABLE_SIN
#undef ENABLE_SIN
#endif

void GCMotor::hold()
{
    shouldHold = true;
    shouldFree = false;
    forward(0);
}

void GCMotor::free()
{
    shouldHold = false;
    shouldFree = true;
    forward(0);
}

void GCMotor::holdImmediately()
{
    digital1 = 0;
    digital2 = 0;
    analog   = 0;
    currentSpeed = 0;
    lastSpecifiedPower = 0;
}

void GCMotor::freeImmediately()
{
    digital1 = 1;
    digital2 = 0;
    analog   = 0;
    currentSpeed = 0;
    lastSpecifiedPower = 0;
}

void GCMotor::setPower(int16_t power)
{
    constexpr int lowestFixPower = 4;
    if (power) {
        power += fixPower;
    } else if (abs(fixPower) >= lowestFixPower) {
        power += fixPower;
    } else {
        if (shouldFree) {
            freeImmediately();
            return;
        } else if (shouldHold) {
            holdImmediately();
            return;
        }
    }
    
    if (power >= 0) {
        digital1 = 0;
        digital2 = 1;
    } else {
        digital1 = 1;
        digital2 = 0;
    }
    
    analog = abs(power);
}

int16_t GCMotor::getCurrentSpeed()
{
    return currentSpeed;
}
