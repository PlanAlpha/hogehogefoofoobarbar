#include "SPIDevice.h"
#include <string.h>
#include <boards.h>

SPIDevice::SPIDevice(Pin devIndex, Baud _baud, Mode _mode) : baud(_baud), mode(_mode), ss(devIndex == Pin::SPI1 ? BOARD_SPI1_NSS_PIN : BOARD_SPI2_NSS_PIN)
{
    if (devIndex == Pin::SPI1) {
        dev = SPI1;
        spi_init(dev);
        spi_master_enable(dev, static_cast<spi_baud_rate>(baud), static_cast<spi_mode>(mode), 0);
    } else {
        dev = SPI2;
        spi_gpio_cfg(
            true,
            PIN_MAP[BOARD_SPI2_NSS_PIN].gpio_device,
            PIN_MAP[BOARD_SPI2_NSS_PIN].gpio_bit,
            PIN_MAP[BOARD_SPI2_SCK_PIN].gpio_device,
            PIN_MAP[BOARD_SPI2_SCK_PIN].gpio_bit,
            PIN_MAP[BOARD_SPI2_MISO_PIN].gpio_bit,
            PIN_MAP[BOARD_SPI2_MOSI_PIN].gpio_bit
        );
        init();
    }
}

void SPIDevice::init()
{
    spi_init(dev);
    spi_master_enable(dev, static_cast<spi_baud_rate>(baud), static_cast<spi_mode>(mode), SPI_DFF_8_BIT | SPI_SW_SLAVE | SPI_SOFT_SS | SPI_FRAME_MSB);
}

uint8_t SPIDevice::write(uint8_t data)
{
    init();
    ss = 1;
    ss = 0;
    delayMicroseconds(100);
    while (1) {
        if (spi_tx(dev, &data, 1)) break;
    }
    while (! spi_is_rx_nonempty(dev)) ;
    return spi_rx_reg(dev);
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
        while (! spi_is_rx_nonempty(dev)) ;
        *buf++ = spi_rx_reg(dev);
    } while (--length);
}
