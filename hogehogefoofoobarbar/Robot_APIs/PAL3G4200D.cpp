#include "PAL3G4200D.h"
#include <usb_serial.h>

PAL3G4200D::PAL3G4200D(I2CDevice::Pin pin) : device(pin, i2cAddress)
{
}

void PAL3G4200D::init()
{
    while (1) {
        uint8_t who = device.read(whoAmI);
        if (who != 211) {
            SerialUSB.print("error reading whoami ");
            SerialUSB.println(who, BIN);
        } else {
            break;
        }
    }
    
    /* disable sleep mode */
    device.write(CTRL_REG1, 0b00001111);
    
    device.write(CTRL_REG2, 0);
    
    device.write(CTRL_REG3, 0b00001000);
    
    device.write(CTRL_REG4, (2 & 0x03) << 4);
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
    Data data;
    device.read(OUT_Z_L, data.buf, 2);
    return data.value;
}
