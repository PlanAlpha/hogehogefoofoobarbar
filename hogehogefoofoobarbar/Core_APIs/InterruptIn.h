#ifndef __InterruptIn__
#define __InterruptIn__

#include "DigitalIn.h"
#include "FunctionPointer.h"
#include <exti.h>

/** A digital interrupt input, used to call a function on a rising or falling edge
 *
 * Example:
 * @code
 * // Flash an LED while waiting for events
 *
 * #include <boards.h>
 * #include <usb_serial.h>
 * #include "Core_APIs/InterruptIn.h"
 * #include "Core_APIs/DigitalOut.h"
 *
 * InterruptIn event(16);
 * DigitalOut led(BOARD_LED_PIN);
 *
 * void trigger() {
 *     SerialUSB.println("triggered!");
 * }
 *
 * int main() {
 *     init();
 *     SerialUSB.begin();
 *     event.attach(&trigger, decltype(event)::Mode::Rising);
 *     while(1) {
 *         led = !led;
 *         delay(250);
 *     }
 * }
 * @endcode
 */
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
    /** Constants to specify which edge to attach
     */
    enum class Mode {
        Rising   = EXTI_RISING,         /** Rising edge */
        Falling  = EXTI_FALLING,        /** Falling edge */
        Changing = EXTI_RISING_FALLING, /** Rising and falling edges */
    };
    
    /** Create an InterruptIn connected to the specified pin
     *
     *  @param pin InterruptIn pin to connect to
     */
    InterruptIn() : DigitalIn(pin) {
        bit = PIN_MAP[pin].gpio_bit;
        port = PIN_MAP[pin].gpio_device->exti_port;
    }
    /** Attach a function to call when an edge occurs on the input
     *
     *  @param fptr A pointer to a void function, or 0 to set as none
     */
    void attach(void (*func)(), Mode mode) {
        delegate.attach(func);
        exti_attach_interrupt(static_cast<afio_exti_num>(bit), port, callback, static_cast<exti_trigger_mode>(mode));
    }
    /** Attach a member function to call when an edge occurs on the input
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template <typename T>
    void attach(T *obj, void (T::*method)(), Mode mode) {
        delegate.attach(obj, method);
        exti_attach_interrupt(static_cast<afio_exti_num>(bit), port, callback, static_cast<exti_trigger_mode>(mode));
    }
    /** Detach a function
     */
    void detach() {
        exti_detach_interrupt(static_cast<afio_exti_num>(bit));
    }
};

template <uint8_t pin> FunctionPointer InterruptIn<pin>::delegate = FunctionPointer();

#endif
