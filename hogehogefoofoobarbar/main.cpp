#include "Robot_APIs/PAL3G4200D.h"
#include "Robot_APIs/GC6050.h"
#include <boards.h>
#include <usb_serial.h>
#include <HardwareSPI.h>
#include <wirish_time.h>
#include "Core_APIs/SPIDevice.h"
#include "Core_APIs/PwmOut.h"
#include <limits>

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    init();
    SerialUSB.begin();
    PwmOut led(BOARD_LED_PIN);
    led = 0;
    const char msg[] = "Hello! this is Maple Mini!\n";
    SPIDevice arduino(SPIDevice::Pin::SPI1, SPIDevice::Baud::B_1_125MHz, SPIDevice::Mode::Mode0);
    while (1) {
        for (uint16_t i = 1; i < std::numeric_limits<uint16_t>::max();) {
            for (char c : msg) {
                if (c == '\0') break;
                if (arduino.read(c) == 1 && c == '\n') {
                    led = ++i;
                }
            }
        }
        for (uint16_t i = std::numeric_limits<uint16_t>::max(); i > 0;) {
            for (char c : msg) {
                if (c == '\0') break;
                if (arduino.read(c) == 1 && c == '\n') {
                    led = --i;
                }
            }
        }
    }
    
    return 0;
}


void commitTest() {
	//hogehogefoofoobarbar
}