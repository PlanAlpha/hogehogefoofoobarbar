#ifndef __SPIDevice__
#define __SPIDevice__

#include <spi.h>
#include <stdint.h>

class SPIDevice {
    spi_dev *dev;
    uint8_t address;
    
public:
    enum class Pin {
        SPI1,
        SPI2,
    };
    enum class Baud {
        DIV_2   = SPI_BAUD_PCLK_DIV_2,
        DIV_4   = SPI_BAUD_PCLK_DIV_4,
        DIV_8   = SPI_BAUD_PCLK_DIV_8,
        DIV_16  = SPI_BAUD_PCLK_DIV_16,
        DIV_32  = SPI_BAUD_PCLK_DIV_32,
        DIV_64  = SPI_BAUD_PCLK_DIV_64,
        DIV_128 = SPI_BAUD_PCLK_DIV_128,
        DIV_256 = SPI_BAUD_PCLK_DIV_256,
    };
    enum class Mode {
        Mode0 = SPI_MODE_0,
        Mode1 = SPI_MODE_1,
        Mode2 = SPI_MODE_2,
        Mode3 = SPI_MODE_3,
    };
    SPIDevice(Pin dev, uint8_t address, Baud baud, Mode mode);
    ~SPIDevice();
    void write(uint8_t reg, uint8_t data);
    void write(uint8_t reg, uint8_t *datas, uint16_t length);
    uint8_t read(uint8_t reg);
    void read(uint8_t reg, uint8_t *buf, uint16_t length);
};


#endif
