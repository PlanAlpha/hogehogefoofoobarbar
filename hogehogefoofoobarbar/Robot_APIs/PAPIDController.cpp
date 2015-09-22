#include "PAPIDController.h"
#include <wirish_time.h>

PAPIDController::PAPIDController(float _Kp, float _Ki, float _Kd, float limit) : Kp(_Kp), Ki(_Ki), Kd(_Kd), integrationLimit(limit)
{
    lastTime = millis();
}

float PAPIDController::next(float error)
{
    integrationValue += error;
    if (integrationValue > integrationLimit) {
        integrationValue = integrationLimit;
    } else if (integrationValue < -integrationLimit) {
        integrationValue = -integrationLimit;
    }
    
    float diff = lastError - error;
    uint16_t delta_t = millis() - lastTime;
    lastTime += delta_t;
    
    return Kp * error + Ki * integrationValue + Kd * diff / delta_t;
}

void PAPIDController::initialize()
{
    integrationValue = 0;
    lastError = 0;
    lastTime = millis();
}
