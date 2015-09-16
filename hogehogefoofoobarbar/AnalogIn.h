#ifndef __AnalogIn__
#define __AnalogIn__

#include <stdint.h>
#include <boards.h>
#include <io.h>

class AnalogIn {
    uint8_t channel;
    volatile uint32_t *SQR1;
    volatile uint32_t *SQR3;
    volatile uint32_t *CR2;
    volatile uint32_t *SR;
    volatile uint32_t *DR;
    
public:
    AnalogIn(uint8_t pin);
    uint16_t read() {
        uint32_t tmp = *SQR1;
        tmp &= ~ADC_SQR1_L;
        *SQR1 = tmp;
        
        *SQR3 = channel;
        *CR2 |= ADC_CR2_SWSTART;
        while (! (*SR & ADC_SR_EOC)) ;
        
        return *DR & ADC_DR_DATA;
    }
    operator uint16_t () {
        return read();
    }
};

#endif
