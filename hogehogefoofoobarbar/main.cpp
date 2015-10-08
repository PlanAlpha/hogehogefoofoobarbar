#include "PlanAlpha.h"

#include <usb_serial.h>
#include "DigitalIn.h"
#include "Core_APIs/InterruptIn.h"
#include <limits>
using namespace PlanAlpha;

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
	delay(2000);
	speaker.play(400, std::numeric_limits<uint16_t>::max()/2, 1000);
    
//    pinMode(8, PWM);
//    pinMode(9, PWM);
//    pwmWrite(8, 0);
//    pwmWrite(9, std::numeric_limits<uint16_t>::max() / 2);
//	rightMotor.forward(0.2);
	
	SerialUSB.begin();
	DigitalIn touch(19);
	DigitalIn touch2(18);
	
	while (1) {
//		SerialUSB.print(forwardLineSensors.read() & PAThreeLineSensors::Left);
		SerialUSB.print(forwardLeftLineSensor.readRawValue());
		SerialUSB.print("\t");
		SerialUSB.print(forwardCenterLineSensor.readRawValue()/2);
		SerialUSB.print("\t");
		SerialUSB.print(forwardRightLineSensor.readRawValue());
		SerialUSB.print("\t");
		SerialUSB.print(touch.read());
		SerialUSB.print("\t");
		SerialUSB.println(touch2.read());
	}
    
    return 0;
}
