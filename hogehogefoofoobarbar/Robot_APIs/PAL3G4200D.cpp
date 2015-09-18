#include "PAL3G4200D.h"
#include <usb_serial.h>

PAL3G4200D::PAL3G4200D(SPIDevice::Pin pin) : device(pin, SPIDevice::Baud::DIV_64, SPIDevice::Mode::Mode3), ss(31)
{
    ss = 0;
}

void PAL3G4200D::init()
{
    while (1) {
        ss = 0;
        delayMicroseconds(5); // 360 hz
        uint8_t who = device.read(whoAmI | 0x80);
        ss = 1;
        if (who != 211) {
            SerialUSB.print("error reading whoami ");
            SerialUSB.println(who);
        } else {
            SerialUSB.println("successful");
            break;
        }
    }
    
    /* disable sleep mode */
    ss = 0;
    delayMicroseconds(15);
    device.write(CTRL_REG1 & 0x7F, 0b00001111);
    ss = 1;
    
    ss = 0;
    delayMicroseconds(15);
    device.write(CTRL_REG1 + 1, 0);
    ss = 1;
    
    ss = 0;
    delayMicroseconds(15);
    device.write(CTRL_REG1 + 2, 0b00001000);
    ss = 1;
    
    ss = 0;
    delayMicroseconds(15);
    device.write(CTRL_REG1 + 3, (2 & 0x03) << 4);
    ss = 1;
}

int16_t PAL3G4200D::readX()
{
    Data data;
    device.read(OUT_X_L, data.buf, 2);
    return data.value;
}

int16_t PAL3G4200D::readY()
{
    Data data;
    device.read(OUT_Y_L, data.buf, 2);
    return data.value;
}

int16_t PAL3G4200D::readZ()
{
//    Data data;
    ss = 0;
    delayMicroseconds(15);
//    device.read(OUT_Z_L | 0x80, data.buf, 2);
    int16_t ret = device.read((OUT_Z_L + 1) | 0x80) << 8;
    ss = 1;
    delayMicroseconds(15);
    ss = 0;
    delayMicroseconds(15);
    ret |= device.read(OUT_Z_L | 0x80);
    ss = 1;
//    return data.value;
    return ret;
}
