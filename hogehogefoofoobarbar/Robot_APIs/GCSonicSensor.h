#ifndef __GCSonicSensor__
#define __GCSonicSensor__

#include "Core_APIs/DigitalInOut.h"

class GCSonicSensor {
    static const int timeout;
    static const int interval;
    DigitalInOut pin;
    unsigned long closeToWall;
    unsigned long farFromWall;
    
public:
    GCSonicSensor(uint8_t pin, unsigned long closeToWall);
    GCSonicSensor(uint8_t pin, unsigned long closeToWall, unsigned long farFromWall);
    bool isClose();
    bool isFar();
    unsigned long getValue();
    unsigned long value = 0;
};

#endif
