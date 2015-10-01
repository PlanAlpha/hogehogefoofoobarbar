#include "PlanAlpha.h"

PASpeaker<25>      PlanAlpha::speaker;
GCADJD             PlanAlpha::leftColorSensor(I2CDevice::Pin::I2C2);
GCADJD             PlanAlpha::rightColorSensor(I2CDevice::Pin::I2C1);
GC6050             PlanAlpha::gyroAcceleroSensor(I2CDevice::Pin::I2C2);
PAL3G4200D         PlanAlpha::gyroSensor(I2CDevice::Pin::I2C2);
PALineSensor       PlanAlpha::forwardLeftLineSensor(5, 1000);
PALineSensor       PlanAlpha::forwardCenterLineSensor(4, 1000);
PALineSensor       PlanAlpha::forwardRightLineSensor(3, 1000);
PALineSensor       PlanAlpha::middleLeftLineSensor(6, 1000);
PALineSensor       PlanAlpha::middleRightLineSensor(7, 1000);
PAThreeLineSensors PlanAlpha::forwardLineSensors(&forwardLeftLineSensor, &forwardCenterLineSensor, &forwardRightLineSensor);

static void __attribute__((constructor)) initializer()
{
    init();
}
