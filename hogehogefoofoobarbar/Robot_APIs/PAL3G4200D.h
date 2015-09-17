#ifndef __PAL3G4200D__
#define __PAL3G4200D__

#include "../Core_APIs/I2CDevice.h"

class PAL3G4200D {
    I2CDevice device;
    
public:
    PAL3G4200D(I2CDevice::Pin pin);
};

#endif
