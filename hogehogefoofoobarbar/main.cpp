#include "PlanAlpha.h"

#include <usb_serial.h>
#include "DigitalIn.h"
#include "Core_APIs/InterruptIn.h"
#include <limits>

using namespace PlanAlpha;

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
	speaker.play(400, std::numeric_limits<uint16_t>::max()/2, 1000);
	delay(2000);
	SerialUSB.begin();
	

	//Linetrace with 2sensors.
	while (1) {
		if (forwardLineSensors.read() & PAThreeLineSensors::Left) {
			leftMotor.forward(-0.5);
			rightMotor.forward(0.5);
		}else if (forwardLineSensors.read() & PAThreeLineSensors::Right){
			leftMotor.forward(0.5);
			rightMotor.forward(-0.5);
		}else {
			rightMotor.forward(0.5);
			rightMotor.forward(0.5);
		}
		delay(100);
	}
	
	
	//view LineSensor's RawValues.
	
	DigitalIn touch(19);
	DigitalIn touch2(18);
	while (1) {
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
