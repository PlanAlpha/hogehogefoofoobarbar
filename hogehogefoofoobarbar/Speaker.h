#ifndef __Speaker__
#define __Speaker__

#include <stdint.h>
#include <timer.h>
#include <boards.h>
#include <io.h>
#include "PwmOut.h"

template <uint8_t pin>
class Speaker {
    static PwmOut *pwm;
    PwmOut pwmInstance;
    static uint32_t count;
    static uint32_t countLimit;
    static void callback() {
        count++;
        if (count > countLimit) {
            pwm->disableIRQ();
            write(0);
        }
    }
    void setPeriod(uint32_t microseconds) {
        pwm->setPeriod(microseconds);
    }
    static void write(uint16_t value) {
        *pwm = value;
    }
    
public:
    Speaker() : pwmInstance(pin) {
        pwm = &pwmInstance;
        pwm->attach(&Speaker<pin>::callback);
        pwm->disableIRQ();
    }
    void play(uint32_t frequency, uint16_t level, uint32_t duration) {
        pwm->disableIRQ();
        uint32_t period = 1000000 / frequency;
        setPeriod(period);
        countLimit = duration * 1000 / period;
        count = 0;
        write(level);
        pwm->enableIRQ();
    }
};

template <uint8_t pin> PwmOut* Speaker<pin>::pwm = NULL;
template <uint8_t pin> uint32_t Speaker<pin>::count = 0;
template <uint8_t pin> uint32_t Speaker<pin>::countLimit = 0;

#endif
