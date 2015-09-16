#include "GCSonicSensor.h"
#include <limits.h>

const int GCSonicSensor::timeout  = 10000;
const int GCSonicSensor::interval = 15;

GCSonicSensor::GCSonicSensor(uint8_t _pin, unsigned long _closeToWall)
: pin(_pin), closeToWall(_closeToWall), farFromWall(INT_MAX)
{
}

GCSonicSensor::GCSonicSensor(uint8_t _pin, unsigned long _closeToWall, unsigned long _farFromWall)
: pin(_pin), closeToWall(_closeToWall), farFromWall(_farFromWall)
{
}

bool GCSonicSensor::isClose()
{
    return value <= closeToWall;
}

bool GCSonicSensor::isFar()
{
    return value >= farFromWall;
}

unsigned long GCSonicSensor::getValue()
{
    pin.output();
    pin.write(0);
    delayMicroseconds(interval);
    pin.write(1);
    delayMicroseconds(interval);
    pin.write(0);
    delayMicroseconds(interval);
    pin.input();
    uint32_t begin = micros();
    while (micros() - begin < timeout) {
        if (! pin) break;
    }
    return value = (micros() - begin) * 17 / 1000;
}
