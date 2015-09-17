#ifndef __SPIDevice__
#define __SPIDevice__

#include <spi.h>
#include <stdint.h>

class SPIDevice {
    static bool isSPI1Initialized;
    static bool isSPI2Initialized;
    spi_dev *dev;
    uint8_t address;
    
public:
    enum class Pin {
        SPI1,
        SPI2,
    };
    SPIDevice(Pin dev, uint8_t address);
    void write(uint8_t reg, uint8_t data);
    void write(uint8_t reg, uint8_t *datas, uint16_t length);
    uint8_t read(uint8_t reg);
    void read(uint8_t reg, uint8_t *buf, uint16_t length);
};


#endif
