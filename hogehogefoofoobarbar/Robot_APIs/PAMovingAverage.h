#ifndef __PAMovingAverage__
#define __PAMovingAverage__

#include <stdint.h>

template <typename T, uint32_t numOfMovingValues>
class PAMovingAverage {
    T movingValues[numOfMovingValues];
    T *movingValuesPoint = movingValues;
    T *movingValuesLimit = movingValues + numOfMovingValues;
    T movingAverage;
    
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
        movingAverage += -*movingValuesPoint / numOfMovingValues + value / numOfMovingValues;
        *movingValuesPoint = value;
        return movingAverage;
    }
};

#endif
