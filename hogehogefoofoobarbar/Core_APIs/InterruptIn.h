#ifndef __InterruptIn__
#define __InterruptIn__

#include "DigitalIn.h"
#include "FunctionPointer.h"
#include <exti.h>

template <uint8_t pin>
class InterruptIn : public DigitalIn
{
    uint8_t bit;
    afio_exti_port port;
    static FunctionPointer delegate;
    static void callback() {
        delegate.call();
    }
    
public:
    enum class Mode {
        Rising = EXTI_RISING,
        Falling = EXTI_FALLING,
        Changing = EXTI_RISING_FALLING,
    };
    
    InterruptIn() : DigitalIn(pin) {
        bit = PIN_MAP[pin].gpio_bit;
        port = PIN_MAP[pin].gpio_device->exti_port;
    }
    void attach(void (*func)(), Mode mode) {
        delegate.attach(func);
        exti_attach_interrupt(static_cast<afio_exti_num>(bit), port, callback, static_cast<exti_trigger_mode>(mode));
    }
    template <typename T>
    void attach(T *obj, void (T::*method)(), Mode mode) {
        delegate.attach(obj, method);
        exti_attach_interrupt(static_cast<afio_exti_num>(bit), port, callback, static_cast<exti_trigger_mode>(mode));
    }
    void detach() {
        exti_detach_interrupt(static_cast<afio_exti_num>(bit));
    }
};

template <uint8_t pin> FunctionPointer InterruptIn<pin>::delegate = FunctionPointer();

#endif
