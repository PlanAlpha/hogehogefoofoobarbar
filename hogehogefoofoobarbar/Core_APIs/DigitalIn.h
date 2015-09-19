#ifndef __DigitalIn__
#define __DigitalIn__

#include <stdint.h>
#include <boards.h>
#include <io.h>

/** A digital input, used for reading the state of a pin
 *
 * Example:
 * @code
 * // Flash an LED while a DigitalIn is true
 *
 * #include <boards.h>
 * #include <wirish_time.h>
 * #include "Core_APIs/DigitalIn.h"
 *
 * DigitalIn enable(5);
 * DigitalOut led(BOARD_LED_PIN);
 *
 * int main() {
 *     init();
 *     while(1) {
 *         if(enable) {
 *             led = !led;
 *         }
 *         delay(250);
 *     }
 * }
 * @endcode
 */
class DigitalIn {
    volatile uint32_t *IDR;
    uint32_t bit;
    stm32_pin_info info;
    
public:
    /** Create a DigitalIn connected to the specified pin
     *
     *  @param pin DigitalIn pin to connect to
     *  @param mode (optional) The initial mode of the pin
     */
    DigitalIn(uint8_t pin, WiringPinMode mode = INPUT);
    /** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    bool read() {
        return *IDR & bit;
    }
    /** An operator shorthand for read()
     */
    operator bool () {
        return read();
    }
    /** Read the digital pulse
     *
     * @param state Pulse state to read
     * @param timeout (optional) Timeout value as microseconds
     */
    uint32_t readPulse(uint8_t state, uint32_t timeout = 100000);
    /** Set the input pin mode
     *
     *  @param mode INPUT, INPUT_FLOATING, INPUT_PULLUP, INPUT_PULLDOWN
     */
    void mode(WiringPinMode mode);
};

#endif
