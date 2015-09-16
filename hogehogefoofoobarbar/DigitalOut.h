#ifndef __DigitalOut__
#define __DigitalOut__

#include <stdint.h>
#include <boards.h>
#include <io.h>

class DigitalOut {
    volatile uint32_t *ODR;
    volatile uint32_t *BSRR;
    volatile uint32_t *BRR;
    uint32_t bit;
    
public:
    DigitalOut(uint8_t pin, WiringPinMode mode = OUTPUT);
    void write(uint8_t value) {
        if (value) {
            *BSRR = bit;
        } else {
            *BRR = bit;
        }
    }
    DigitalOut& operator = (uint8_t value) {
        write(value);
        return *this;
    }
    void toggle() {
        *ODR = *ODR ^ bit;
    }
};

#endif
