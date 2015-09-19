#ifndef __SPIDevice__
#define __SPIDevice__

#include <spi.h>
#include <stdint.h>
#include "DigitalOut.h"

class SPIDevice {
public:
    enum class Pin {
        SPI1,
        SPI2,
    };
    enum class Baud {
        B_18MHz      = SPI_BAUD_PCLK_DIV_2,
        B_9MHz       = SPI_BAUD_PCLK_DIV_4,
        B_4_5MHz     = SPI_BAUD_PCLK_DIV_8,
        B_2_25MHz    = SPI_BAUD_PCLK_DIV_16,
        B_1_125MHz   = SPI_BAUD_PCLK_DIV_32,
        B_562_500KHz = SPI_BAUD_PCLK_DIV_64,
        B_281_250KHz = SPI_BAUD_PCLK_DIV_128,
        B_140_625Khz = SPI_BAUD_PCLK_DIV_256,
    };
    enum class Mode {
        Mode0 = SPI_MODE_0,
        Mode1 = SPI_MODE_1,
        Mode2 = SPI_MODE_2,
        Mode3 = SPI_MODE_3,
    };
    
private:
    spi_dev *dev;
    Baud baud;
    Mode mode;
    DigitalOut ss;
    
public:
    SPIDevice(Pin dev, Baud baud, Mode mode);
    uint8_t write(uint8_t data);
    void write(uint8_t reg, uint8_t data);
    void write(uint8_t reg, uint8_t *datas, uint32_t length);
    uint8_t read(uint8_t reg);
    void read(uint8_t reg, uint8_t *buf, uint32_t length);
    void init();
};


#endif
