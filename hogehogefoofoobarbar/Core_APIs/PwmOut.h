#ifndef __PwmOut__
#define __PwmOut__

#include <stdint.h>
#include <boards.h>
#include <io.h>

/** A pulse-width modulation digital output
 *
 * Example
 * @code
 * // Fade a led on.
 * #include <boards.h>
 * #include "Core_APIs/PwmOut.h"
 *
 * PwmOut led(BOARD_LED_PIN);
 *
 * int main() {
 *     init();
 *     while(1) {
 *         for (int i = 0; i <= 255; i++) {
 *             led = i * 257;
 *             delay(200);
 *         }
 *     }
 * }
 * @endcode
 */
class PwmOut {
    volatile uint32_t *ccr;
    volatile uint32_t *psc;
    volatile uint32_t *arr;
    stm32_pin_info info;
    
public:
    /** Create a PwmOut connected to the specified pin
     *
     *  @param pin PwmOut pin to connect to
     *  @param mode (optional) The initial mode of the pin
     */
    PwmOut(uint8_t pin, WiringPinMode mode = PWM);
    /** Set the ouput duty-cycle, specified as a 16-bits value
     *
     *  @param value A 16-bits value representing the output duty-cycle
     */
    void write(uint16_t value) {
        *ccr = value;
    }
    /** A operator shorthand for write()
     */
    PwmOut& operator = (uint16_t value) {
        write(value);
        return *this;
    }
    /** Set the PWM period, specified in micro-seconds (uint32_t), keeping the duty cycle the same.
     */
    void setPeriod(uint32_t microseconds);
    /** Attach a function to call when a capture/compare interrupt occurs
     *
     *  @param fptr A pointer to a void function, or 0 to set as none
     */
    void attach(voidFuncPtr func) {
        timer_attach_interrupt(info.timer_device, info.timer_channel, func);
    }
    /** Enable a timer interrupt.
     */
    void enableIRQ() {
        timer_enable_irq(info.timer_device, info.timer_channel);
    }
    /** Disable a timer interrupt.
     */
    void disableIRQ() {
        timer_disable_irq(info.timer_device, info.timer_channel);
    }
};

#endif
