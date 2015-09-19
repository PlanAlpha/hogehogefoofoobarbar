#ifndef __PAMovingAverage__
#define __PAMovingAverage__

#include <stdint.h>

template <typename T, uint32_t numOfMovingValues>
class PAMovingAverage {
    float movingValues[numOfMovingValues];
    float *movingValuesPoint = movingValues;
    float *movingValuesLimit = movingValues + numOfMovingValues;
    float movingAverage;
    
public:
    PAMovingAverage() {
    }
    void initialize(T value) {
        while (movingValuesPoint != movingValuesLimit) {
            *movingValuesPoint++ = value;
        }
        movingValuesPoint = movingValues;
        movingAverage = value;
    }
    T addValue(T value) {
        if (++movingValuesPoint == movingValuesLimit) {
            movingValuesPoint = movingValues;
        }
        movingAverage += -*movingValuesPoint / numOfMovingValues + static_cast<float>(value) / numOfMovingValues;
        *movingValuesPoint = value;
        return static_cast<T>(movingAverage);
    }
};

#endif
