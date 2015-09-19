#include "Robot_APIs/PAL3G4200D.h"
#include "Robot_APIs/GC6050.h"
#include <boards.h>
#include <usb_serial.h>
#include <HardwareSPI.h>
#include <wirish_time.h>
#include "Core_APIs/SPIDevice.h"
#include "Core_APIs/DigitalOut.h"

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    init();
    SerialUSB.begin();
    DigitalOut led(BOARD_LED_PIN);
    led = 0;
    const char msg[] = "Hello! this is Maple Mini!\n";
    SPIDevice arduino(SPIDevice::Pin::SPI2, SPIDevice::Baud::B_1_125MHz, SPIDevice::Mode::Mode0);
    while (1) {
        for (char c : msg) {
            if (c == '\0') break;
            arduino.write(c);
        }
    }
    
    return 0;
}
