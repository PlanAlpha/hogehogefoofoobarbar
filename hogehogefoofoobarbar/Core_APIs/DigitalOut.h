#ifndef __DigitalOut__
#define __DigitalOut__

#include <stdint.h>
#include <boards.h>
#include <io.h>

/** A digital output, used for setting the state of a pin
 *
 * Example:
 * @code
 * // Toggle a LED
 * #include <boards.h>
 * #include <wirish_time.h>
 * #include "Core_APIs/DigitalOut.h"
 *
 * DigitalOut led(BOARD_LED_PIN);
 *
 * int main() {
 *     init();
 *     while(1) {
 *         led = !led;
 *         delay(200);
 *     }
 * }
 * @endcode
 */
class DigitalOut {
    volatile uint32_t *ODR;
    volatile uint32_t *BSRR;
    volatile uint32_t *BRR;
    uint32_t bit;
    
public:
    /** Create a DigitalOut connected to the specified pin
     *
     *  @param pin DigitalOut pin to connect to
     *  @param mode (optional) The initial mode of the pin
     */
    DigitalOut(uint8_t pin, WiringPinMode mode = OUTPUT);
    /** Set the output, specified as 0 or 1 (int)
     *
     *  @param value An integer specifying the pin output value,
     *      0 for logical 0, 1 (or any other non-zero value) for logical 1
     */
    void write(uint8_t value) {
        if (value) {
            *BSRR = bit;
        } else {
            *BRR = bit;
        }
    }
    /** A shorthand for write()
     */
    DigitalOut& operator = (uint8_t value) {
        write(value);
        return *this;
    }
    /** Toggle the output
     */
    void toggle() {
        *ODR = *ODR ^ bit;
    }
};

#endif
