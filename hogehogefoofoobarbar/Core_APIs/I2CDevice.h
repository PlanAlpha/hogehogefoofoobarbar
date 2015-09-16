#ifndef __I2CDevice__
#define __I2CDevice__

#include <stdint.h>
#include <i2c.h>

class I2CDevice {
    static bool isI2C1Initialized;
    static bool isI2C2Initialized;
    i2c_dev *dev;
    uint8_t address;
    
public:
    enum class Pin {
        I2C1,
        I2C2,
    };
    I2CDevice(Pin dev, uint8_t address);
    void write(uint8_t reg, uint8_t data);
    void write(uint8_t reg, uint8_t *datas, uint16_t length);
    uint8_t read(uint8_t reg);
    void read(uint8_t reg, uint8_t *buf, uint16_t length);
};

#endif
