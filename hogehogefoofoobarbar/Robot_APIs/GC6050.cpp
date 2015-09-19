#include "GC6050.h"

GC6050::GC6050(I2CDevice::Pin dev, bool isAD0Pulluped) : i2c(dev, i2cAddress | isAD0Pulluped)
{
    if (i2c.read(whoAmIAddress) != i2cAddress) {
    }
    
    uint8_t power = i2c.read(powerAddress);
    power &= ~(1 << 6);
    i2c.write(powerAddress, power);
    
    updateValues();
}

void GC6050::updateValues()
{
    union SensorValue {
        uint8_t buf[6];
        uint16_t value[3];
    };
    SensorValue accel;
    i2c.read(accelAddress, accel.buf, 6);
#define convertAccel(v) (static_cast<float>((v) / 16384.0 * 9.81))
    currentAccelValue = {
        convertAccel(accel.value[0]) - accelOffsets.x,
        convertAccel(accel.value[1]) - accelOffsets.y,
        convertAccel(accel.value[2]) - accelOffsets.z
    };
#undef convertAccel

    SensorValue gyro;
    i2c.read(gyroAddress, gyro.buf, 6);
#define convertGyro(v) static_cast<float>((v) / 301.0)
    currentGyroValue = {
        convertGyro(gyro.value[0]) - gyroOffsets.x,
        convertGyro(gyro.value[1]) - gyroOffsets.y,
        convertGyro(gyro.value[2]) - gyroOffsets.z
    };
#undef convertGyro
}

void GC6050::setOffsets()
{
    accelOffsets.x = currentAccelValue.x;
    accelOffsets.y = currentAccelValue.y;
    accelOffsets.z = currentAccelValue.z;
    gyroOffsets.x  = currentGyroValue.x;
    gyroOffsets.y  = currentGyroValue.y;
    gyroOffsets.z  = currentGyroValue.z;
}
