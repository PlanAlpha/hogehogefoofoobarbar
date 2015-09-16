#ifndef __DigitalInOut__
#define __DigitalInOut__

#include <stdint.h>
#include <io.h>
#include "DigitalIn.h"
#include "DigitalOut.h"

class DigitalInOut : public DigitalIn, public DigitalOut {
    volatile uint32_t *cr;
    uint32_t shift;
    volatile uint32_t *ODR;
    uint8_t pin;
    
public:
    DigitalInOut(uint8_t pin);
    void output() {
        uint32_t tmp = *cr;
        
        tmp &= ~(0xF << shift);
        tmp |= GPIO_OUTPUT_OD << shift;
        *cr = tmp;
    }
    void input() {
        uint32_t tmp = *cr;
        
        tmp &= ~(0xF << shift);
        tmp |= GPIO_INPUT_FLOATING << shift;
        *cr = tmp;
    }
    void mode(WiringPinMode pull) {
        uint32_t tmp = *cr;
        
        tmp &= ~(0xF << shift);
        
        switch (pull) {
            case OUTPUT:
            case OUTPUT_OPEN_DRAIN:
            case INPUT:
            case INPUT_FLOATING:
                *cr = tmp;
                break;
                
            case INPUT_PULLUP:
                tmp |= GPIO_INPUT_PD << shift;
                *ODR |= BIT(pin);
                *cr = tmp;
                break;
                
            case INPUT_PULLDOWN:
                *ODR &= ~BIT(pin);
                *cr = tmp;
                break;
                
            default:
                ASSERT(0);
                break;
        }
    }
};

#endif
