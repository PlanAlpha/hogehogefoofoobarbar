#ifndef __AnalogIn__
#define __AnalogIn__

#include <stdint.h>
#include <boards.h>
#include <io.h>

/** An analog input, used for reading the voltage on a pin
 *
 * Example:
 * @code
 * // Print messages when the AnalogIn is greater than 50%
 *
 * #include <boards.h>
 * #include <usb_serial.h>
 * #include "Core_APIs/Analogin.h"
 *
 * AnalogIn temperature(11);
 *
 * int main() {
 *     init();
 *     SerialUSB.begin();
 *     while(1) {
 *         if(temperature > 32767) {
 *             SerialUSB.print("Too hot! (%f"); SerialUSB.print(temperature.read()); SerialUSB.print(")");
 *         }
 *     }
 * }
 * @endcode
 */
class AnalogIn {
    uint8_t channel;
    volatile uint32_t *SQR1;
    volatile uint32_t *SQR3;
    volatile uint32_t *CR2;
    volatile uint32_t *SR;
    volatile uint32_t *DR;
    
public:
    /** Create an AnalogIn, connected to the specified pin
     *
     * @param pin AnalogIn pin to connect to
     */
    AnalogIn(uint8_t pin);
    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalised to a 16-bit value
     */
    uint16_t read() {
        uint32_t tmp = *SQR1;
        tmp &= ~ADC_SQR1_L;
        *SQR1 = tmp;
        
        *SQR3 = channel;
        *CR2 |= ADC_CR2_SWSTART;
        while (! (*SR & ADC_SR_EOC)) ;
        
        return *DR & ADC_DR_DATA;
    }
    /** An operator shorthand for read()
     *
     * The uint16_t() operator can be used as a shorthand for read() to simplify common code sequences
     *
     * Example:
     * @code
     * uint16_t x = volume.read();
     * uint16_t x = volume;
     *
     * if(volume.read() > 16383) { ... }
     * if(volume > 16383) { ... }
     * @endcode
     */
    operator uint16_t () {
        return read();
    }
};

#endif
