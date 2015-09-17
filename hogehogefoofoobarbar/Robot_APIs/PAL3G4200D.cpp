#include "PAL3G4200D.h"
#include <usb_serial.h>

PAL3G4200D::PAL3G4200D(SPIDevice::Pin pin) : device(pin, SPIDevice::Baud::DIV_8, SPIDevice::Mode::Mode2)
{
    if (device.read(whoAmI) != 211) {
        SerialUSB.println("error reading whoami");
    }
    
    /* disable sleep mode */
    uint8_t ctrl1 = device.read(CTRL_REG1);
    ctrl1 &= ~(1 << PD);
    device.write(CTRL_REG1, ctrl1);
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
