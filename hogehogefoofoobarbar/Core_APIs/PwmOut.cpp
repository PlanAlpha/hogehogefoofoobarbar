#include "PwmOut.h"

PwmOut::PwmOut(uint8_t _pin, WiringPinMode mode)
{
    ASSERT(_pin < BOARD_NR_GPIO_PINS);
    info = PIN_MAP[_pin];
    timer_dev *dev = info.timer_device;
    uint8_t channel = info.timer_channel;
    ccr = reinterpret_cast<volatile uint32_t *>(&(dev->regs).gen->CCR1 + (channel - 1));
    psc = reinterpret_cast<volatile uint32_t *>(&((dev->regs).bas->PSC));
    arr = reinterpret_cast<volatile uint32_t *>(&((dev->regs).bas->ARR));
    ASSERT(dev);
    
    gpio_pin_mode pinmode = GPIO_AF_OUTPUT_PP;
    switch (mode) {
        case PWM:
            /* pinmode = GPIO_AF_OUTPUT_PP; */
            break;
            
        case PWM_OPEN_DRAIN:
            pinmode = GPIO_AF_OUTPUT_OD;
            break;
            
        default:
            ASSERT(0);
            break;
    }
    
    gpio_set_mode(info.gpio_device, info.gpio_bit, pinmode);
    timer_set_mode(dev, channel, TIMER_PWM);
}

void PwmOut::setPeriod(uint32_t microseconds)
{
    uint32_t period_cyc = microseconds * CYCLES_PER_MICROSECOND;
    uint16_t prescaler = static_cast<uint16_t>(period_cyc / ((1 << 16) - 1) + 1);
    uint16_t overflow = static_cast<uint16_t>(period_cyc / prescaler + 0.5);
    *psc = prescaler - 1;
    *arr = overflow;
}
