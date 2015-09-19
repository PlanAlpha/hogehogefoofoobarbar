#include "I2CDevice.h"
#include <string.h>
#include <usb_serial.h>

bool I2CDevice::isI2C1Initialized = false;
bool I2CDevice::isI2C2Initialized = false;

I2CDevice::I2CDevice(Pin devIndex, uint8_t _address) : address(_address)
{
    if (devIndex == Pin::I2C1) {
        dev = I2C1;
        if (! isI2C1Initialized) {
            i2c_init(dev);
            i2c_master_enable(dev, 0);
            isI2C1Initialized = true;
        }
    } else {
        dev = I2C2;
        if (! isI2C2Initialized) {
            i2c_init(dev);
            i2c_master_enable(dev, 0);
            isI2C2Initialized = true;
        }
    }
}

void I2CDevice::write(uint8_t reg, uint8_t data)
{
    write(reg, &data, 1);
}

void I2CDevice::write(uint8_t reg, uint8_t *datas, uint16_t length)
{
    uint8_t buf[length + 1];
    memcpy(reinterpret_cast<uint8_t *>(buf) + 1, datas, length);
    buf[0] = reg;
    i2c_msg msgs[] = {
        {
            address,
            0,
            static_cast<uint16_t>(length + 1),
            0,
            buf
        },
    };
    switch (i2c_master_xfer(dev, msgs, 1, 1000)) {
        case I2C_ERROR_PROTOCOL:
            SerialUSB.println("protocol error occured");
            break;
            
        case I2C_ERROR_TIMEOUT:
            SerialUSB.println("timeout occured");
            break;
            
        default:
            return;
    }
    i2c_init(dev);
    i2c_master_enable(dev, 0);
}

uint8_t I2CDevice::read(uint8_t reg)
{
    uint8_t buf[1];
    read(reg, buf, 1);
    return buf[0];
}

void I2CDevice::read(uint8_t reg, uint8_t *buf, uint16_t length)
{
    i2c_msg msgs[] = {
        {
            address,
            0,
            1,
            0,
            &reg
        },
        {
            address,
            I2C_MSG_READ,
            length,
            0,
            buf
        },
    };
    switch (i2c_master_xfer(dev, msgs, 2, 1000)) {
        case I2C_ERROR_PROTOCOL:
            SerialUSB.println("protocol error occured");
            break;
            
        case I2C_ERROR_TIMEOUT:
            SerialUSB.println("timeout occured");
            break;
            
        default:
            return;
    }
    i2c_init(dev);
    i2c_master_enable(dev, 0);
}
