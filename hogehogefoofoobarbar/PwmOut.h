#ifndef __PwmOut__
#define __PwmOut__

#include <stdint.h>
#include <boards.h>
#include <io.h>

class PwmOut {
    volatile uint32_t *ccr;
    volatile uint32_t *psc;
    volatile uint32_t *arr;
    stm32_pin_info info;
    
public:
    PwmOut(uint8_t pin, WiringPinMode mode = PWM);
    void write(uint16_t value) {
        *ccr = value;
    }
    PwmOut& operator = (uint16_t value) {
        write(value);
        return *this;
    }
    void setPeriod(uint32_t microseconds);
    void attach(voidFuncPtr func) {
        timer_attach_interrupt(info.timer_device, info.timer_channel, func);
    }
    void enableIRQ() {
        timer_enable_irq(info.timer_device, info.timer_channel);
    }
    void disableIRQ() {
        timer_disable_irq(info.timer_device, info.timer_channel);
    }
};

#endif
