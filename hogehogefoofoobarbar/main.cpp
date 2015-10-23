#include "PlanAlpha.h"

#include <usb_serial.h>
#include "DigitalIn.h"
#include "Core_APIs/InterruptIn.h"
#include <limits>

using namespace PlanAlpha;

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
	SerialUSB.begin();
	speaker1.play(400, std::numeric_limits<uint16_t>::max()/2, 1000);
	speaker2.play(400, std::numeric_limits<uint16_t>::max()/2, 1000);
	delay(2000);
	
	//Linetrace with 2sensors.
//	double speed = 0.3;
//	while (1) {
//		if (forwardLineSensors.read() & PAThreeLineSensors::Left) {
//			leftMotor.forward(-speed);
//			rightMotor.forward(-speed);
//			delay(1000);
//		}else{
//			leftMotor.forward(speed);
//			rightMotor.forward(speed);
//		}
//	}
	
	double motorSpeed = 0.2;
	while (1) {
		if (forwardLineSensors.read() & PAThreeLineSensors::Left) {
			if (forwardLineSensors.read() & PAThreeLineSensors::Right) {
				//akaaaaaaaaaaaaaaaaaaaaaaan
				speaker1.play(440, std::numeric_limits<uint16_t>::max()/2, 100);
			}else{
				speaker1.play(600, std::numeric_limits<uint16_t>::max()/2, 100);
				leftMotor.forward(motorSpeed*-1);
				rightMotor.forward(motorSpeed);
			}
		}else{
			if(forwardLineSensors.read() & PAThreeLineSensors::Right) {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed*-1);
			}else{
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
	
	}
	
	//view LineSensor's RawValues.
	
	DigitalIn touch(19);
	DigitalIn touch2(18);
	while (1) {
//		speaker.play(440, std::numeric_limits<uint16_t>::max()/2, 50);
//		delay(100);
		SerialUSB.print(forwardLeftLineSensor.readRawValue());
		SerialUSB.print("\t");
		SerialUSB.print(forwardCenterLineSensor.readRawValue());
		SerialUSB.print("\t");
		SerialUSB.print(forwardRightLineSensor.readRawValue());
		SerialUSB.print("\t");
		SerialUSB.print(touch.read());
		SerialUSB.print("\t");
		SerialUSB.println(touch2.read());
	}
	
	return 0;
}