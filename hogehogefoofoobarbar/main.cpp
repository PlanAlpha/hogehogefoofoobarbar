#include <wirish.h>
#include <i2c.h>
#include <limits>
#include <stdint.h>
#undef max
#include "PlanAlpha.h"

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    
//    pinMode(8, PWM);
//    pinMode(9, PWM);
//    pwmWrite(8, 0);
//    pwmWrite(9, std::numeric_limits<uint16_t>::max() / 2);
    PlanAlpha::rightMotor.forward(0.2);
    while (1) {
    }
    
    return 0;
}
