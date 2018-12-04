//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKWIRINGPI_THREE_AXIS_ACCELEROMETER_H
#define NUNCHUCKWIRINGPI_THREE_AXIS_ACCELEROMETER_H

#include <mutex>

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

    class NunchuckAccelerometer : ThreeAxisAccelerometer<int>{
    public:
        NunchuckAccelerometer();
        ThreeAxisAcceleration<int> getAcceleration() {
            std::lock_guard <std::mutex> lock(internal_mutex);
            return acceleration;
        }
        void updateAcceleration(int accelerationOnX, int accelerationOnY, int accelerationOnZ){
            std::lock_guard <std::mutex> lock(internal_mutex);
            acceleration.X = accelerationOnX;
            acceleration.Y = accelerationOnY;
            acceleration.Z = accelerationOnZ;
        }
    private:
        ThreeAxisAcceleration<int> acceleration;
        std::mutex internal_mutex;
    };
}

#endif //NUNCHUCKWIRINGPI_ACCELEROMETER_H
