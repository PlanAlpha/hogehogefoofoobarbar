#include "DigitalOut.h"

DigitalOut::DigitalOut(uint8_t pin, WiringPinMode mode)
{
    ASSERT(pin < BOARD_NR_GPIO_PINS);
    
    stm32_pin_info info = PIN_MAP[pin];
    gpio_dev *dev = info.gpio_device;
    uint8_t channel = info.gpio_bit;
    gpio_reg_map *regs = dev->regs;
    ODR = reinterpret_cast<volatile uint32_t *>(&regs->ODR);
    BSRR = reinterpret_cast<volatile uint32_t *>(&regs->BSRR);
    BRR = reinterpret_cast<volatile uint32_t *>(&regs->BRR);
    bit = BIT(channel);
    
    gpio_pin_mode pinmode = GPIO_OUTPUT_PP;
    switch (mode) {
        case OUTPUT:
            /* pinmode = GPIO_OUTPUT_PP; */
            break;
            
        case OUTPUT_OPEN_DRAIN:
            pinmode = GPIO_OUTPUT_OD;
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
