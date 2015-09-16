#include "DigitalInOut.h"

DigitalInOut::DigitalInOut(uint8_t _pin) : DigitalIn(_pin), DigitalOut(_pin)
{
    gpio_reg_map *regs = PIN_MAP[_pin].gpio_device->regs;
    cr = reinterpret_cast<volatile uint32_t *>(&regs->CRL + (_pin >> 3));
    shift = (_pin & 0x7) * 4;
    ODR = reinterpret_cast<volatile uint32_t *>(&regs->ODR);
    pin = _pin;
}
