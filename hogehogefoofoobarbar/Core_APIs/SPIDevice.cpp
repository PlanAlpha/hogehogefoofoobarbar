#include "SPIDevice.h"
#include <string.h>

bool SPIDevice::isSPI1Initialized = false;
bool SPIDevice::isSPI2Initialized = false;

SPIDevice::SPIDevice(Pin devIndex, uint8_t _address) : address(_address)
{
    if (devIndex == Pin::SPI1) {
        dev = SPI1;
        if (! isSPI1Initialized) {
            spi_init(dev);
            spi_master_enable(dev, SPI_BAUD_PCLK_DIV_2, SPI_MODE_0, 0);
            isSPI1Initialized = true;
        }
    } else {
        dev = SPI2;
        if (! isSPI2Initialized) {
            spi_init(dev);
            spi_master_enable(dev, SPI_BAUD_PCLK_DIV_2, SPI_MODE_0, 0);
            isSPI2Initialized = true;
        }
    }
}

void SPIDevice::write(uint8_t reg, uint8_t data)
{
    write(reg, &data, 1);
}

void SPIDevice::write(uint8_t reg, uint8_t *datas, uint16_t length)
{
    uint8_t buf[length + 1];
    memcpy(buf + 1, datas, length);
    buf[0] = reg;
    spi_tx(dev, datas, length);
}

uint8_t SPIDevice::read(uint8_t reg)
{
    uint8_t buf;
    read(reg, &buf, 1);
    return buf;
}

void SPIDevice::read(uint8_t reg, uint8_t *buf, uint16_t length)
{
    spi_tx(dev, &reg, 1);
    do {
        while (! spi_is_rx_nonempty(dev)) ;
        *buf++ = spi_rx_reg(dev);
    } while (--length);
}
