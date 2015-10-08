#include "GCMotor.h"
#include <limits>

GCMotor::GCMotor(uint8_t _pin1, uint8_t _pin2) : pin1(_pin1), pin2(_pin2)
{
    free();
}

void GCMotor::forward(int32_t power)
{
    if (power >= 0) {
        pin2 = 0;
        pin1 = static_cast<uint16_t>(power);
    } else {
        pin1 = 0;
        pin2 = static_cast<uint16_t>(-power);
    }
}

void GCMotor::forward(float power)
{
    if (power >= 1) {
        forward(std::numeric_limits<int32_t>::max());
    } else if (power <= -1) {
        forward(std::numeric_limits<int32_t>::min());
    } else {
        forward(static_cast<int32_t>(power * std::numeric_limits<uint16_t>::max()));
    }
}

void GCMotor::free()
{
    pin1 = 0;
    pin2 = 0;
}
