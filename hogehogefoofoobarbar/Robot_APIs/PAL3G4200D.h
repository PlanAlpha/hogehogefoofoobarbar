#ifndef __PAL3G4200D__
#define __PAL3G4200D__

#include "../Core_APIs/I2CDevice.h"

class PAL3G4200D {
    static constexpr uint8_t i2cAddress = 104;
    static constexpr uint8_t whoAmI = 15;
    static constexpr uint8_t CTRL_REG1 = 32;
    static constexpr uint8_t PD = 3;
    static constexpr uint8_t CTRL_REG2 = 33;
    static constexpr uint8_t CTRL_REG3 = 34;
    static constexpr uint8_t CTRL_REG4 = 35;
    static constexpr uint8_t OUT_X_L = 40;
    static constexpr uint8_t OUT_Y_L = 42;
    static constexpr uint8_t OUT_Z_L = 44;
    I2CDevice device;
    union Data {
        uint8_t buf[2];
        uint16_t value;
    };
    
public:
    PAL3G4200D(I2CDevice::Pin pin);
    void init();
    int16_t readX();
    int16_t readY();
    int16_t readZ();
};

#endif
