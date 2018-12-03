//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKWIRINGPI_THREE_AXIS_ACCELEROMETER_H
#define NUNCHUCKWIRINGPI_THREE_AXIS_ACCELEROMETER_H

namespace nunchuckwiringpi {
    template<class T>
    typedef struct ThreeAxisAcceleration{
        T X;
        T Y;
        T Z;
    };

    template <class T>
    class ThreeAxisAccelerometer {
        virtual ThreeAxisAcceleration<T> getAcceleration() = 0;
    };
}

#endif //NUNCHUCKWIRINGPI_ACCELEROMETER_H
