#include "AnalogIn.h"

AnalogIn::AnalogIn(uint8_t pin)
{
    ASSERT(pin < BOARD_NR_GPIO_PINS);
    stm32_pin_info info = PIN_MAP[pin];
    const adc_dev *dev = info.adc_device;
    channel = info.adc_channel;
    ASSERT(dev);
    
    adc_reg_map *regs = dev->regs;
    SQR1 = reinterpret_cast<volatile uint32_t *>(&regs->SQR1);
    SQR3 = reinterpret_cast<volatile uint32_t *>(&regs->SQR3);
    CR2 = reinterpret_cast<volatile uint32_t *>(&regs->CR2);
    SR = reinterpret_cast<volatile uint32_t *>(&regs->SR);
    DR = reinterpret_cast<volatile uint32_t *>(&regs->DR);
    
    gpio_set_mode(info.gpio_device, info.gpio_bit, GPIO_INPUT_ANALOG);
    if (info.timer_device) {
        timer_set_mode(info.timer_device, info.timer_channel, TIMER_DISABLED);
    }
}
