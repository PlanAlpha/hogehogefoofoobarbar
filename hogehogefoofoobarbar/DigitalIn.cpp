#include "DigitalIn.h"

DigitalIn::DigitalIn(uint8_t pin, WiringPinMode mode)
{
    ASSERT(pin < BOARD_NR_GPIO_PINS);
    stm32_pin_info info = PIN_MAP[pin];
    gpio_dev *dev = info.gpio_device;
    uint8_t channel = info.gpio_bit;
    gpio_reg_map *regs = dev->regs;
    IDR = reinterpret_cast<volatile uint32_t *>(&regs->IDR);
    bit = BIT(channel);
    
    gpio_pin_mode pinmode = GPIO_INPUT_FLOATING;
    switch (mode) {
        case INPUT:
        case INPUT_FLOATING:
            /* pinmode = GPIO_INPUT_FLOATING */
            break;
            
        case INPUT_PULLDOWN:
            pinmode = GPIO_INPUT_PD;
            break;
            
        case INPUT_PULLUP:
            pinmode = GPIO_INPUT_PU;
            break;
            
        default:
            ASSERT(0);
            break;
    }
    
    gpio_set_mode(dev, channel, pinmode);
    if (info.timer_device) {
        timer_set_mode(info.timer_device, info.timer_channel, TIMER_DISABLED);
    }
}
