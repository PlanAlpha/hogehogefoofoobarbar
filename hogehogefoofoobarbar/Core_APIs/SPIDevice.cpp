#include "SPIDevice.h"
#include <string.h>
#include <usb_serial.h>
#include <boards.h>

SPIDevice::SPIDevice(Pin devIndex, Baud baud, Mode mode)
{
    if (devIndex == Pin::SPI1) {
        dev = SPI1;
        spi_init(dev);
        spi_master_enable(dev, static_cast<spi_baud_rate>(baud), static_cast<spi_mode>(mode), 0);
    } else {
        dev = SPI2;
        spi_init(dev);
        spi_gpio_cfg(true, PIN_MAP[31].gpio_device, PIN_MAP[31].gpio_bit, PIN_MAP[30].gpio_device, PIN_MAP[30].gpio_bit, PIN_MAP[29].gpio_bit, PIN_MAP[28].gpio_bit);
        spi_master_enable(dev, static_cast<spi_baud_rate>(baud), static_cast<spi_mode>(mode), SPI_DFF_8_BIT | SPI_SW_SLAVE | SPI_SOFT_SS | SPI_FRAME_MSB);
    }
}

void SPIDevice::write(uint8_t reg, uint8_t data)
{
    write(reg, &data, 1);
}

void SPIDevice::write(uint8_t reg, uint8_t *datas, uint32_t length)
{
    uint8_t buf[length + 1];
    memcpy(buf + 1, datas, length);
    buf[0] = reg;
    uint8_t remind = length + 1;
    do {
        remind -= spi_tx(dev, buf, remind);
    } while (remind);
}

uint8_t SPIDevice::read(uint8_t reg)
{
    uint8_t buf;
    read(reg, &buf, 1);
    return buf;
}

void SPIDevice::read(uint8_t reg, uint8_t *buf, uint32_t length)
{
    do {
        if (spi_tx(dev, &reg, 1)) break;
        while (! spi_is_rx_nonempty(dev)) ;
        spi_rx_reg(dev);
    } while (1);
    do {
        while (! spi_is_rx_nonempty(dev)) ;//SerialUSB.println("waiting for a response");
        *buf++ = spi_rx_reg(dev);
//        SerialUSB.println("response has read");
    } while (--length);
}
