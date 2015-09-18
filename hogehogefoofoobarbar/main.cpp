#include "Robot_APIs/PAL3G4200D.h"
#include <boards.h>
#include <usb_serial.h>
#include <HardwareSPI.h>

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    init();
    SerialUSB.begin();
    PAL3G4200D gyro(I2CDevice::Pin::I2C1);
    SerialUSB.read();
//    DigitalOut ss(31);
//    HardwareSPI spi(2);
//    spi.begin(SPI_1_125MHZ, 1, SPI_MODE_3);
//    while (1) {
//        ss = 0;
//        delayMicroseconds(20);
//        SerialUSB.println(spi.transfer(15 | 0x80));
//        ss = 1;
//    }
    gyro.init();
    while (1) {
        SerialUSB.println(gyro.readZ());
    }
    return 0;
}
