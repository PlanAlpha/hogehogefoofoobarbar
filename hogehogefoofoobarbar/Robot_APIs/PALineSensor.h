#ifndef __PALineSensor__
#define __PALineSensor__

#include "../Core_APIs/AnalogIn.h"

class PALineSensor {
    AnalogIn pin;
    const uint16_t blackValue;
    
public:
    PALineSensor(uint8_t pin, uint16_t blackValue);
    bool isBlack() {
        return pin <= blackValue;
    }
    operator bool () {
        return isBlack();
    }
    uint16_t readRawValue() {
        return pin;
    }
};

#endif
