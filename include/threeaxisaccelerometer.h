//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKADAPTER_THREE_AXIS_ACCELEROMETER_H
#define NUNCHUCKADAPTER_THREE_AXIS_ACCELEROMETER_H

#include <mutex>

namespace nunchuckadapter {
    template<class T>
    struct ThreeAxisAcceleration{
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
        static const int MIN_ACCELEROMETER_VALUE = 0;
        static const int MAX_ACCELEROMETER_VALUE = 1023;

        NunchuckAccelerometer(const int accelerationOnX,const  int accelerationOnY,const  int accelerationOnZ){
            acceleration = {
                    accelerationOnX,
                    accelerationOnY,
                    accelerationOnZ
            };
        }

        NunchuckAccelerometer() {
            acceleration = {
                    MAX_ACCELEROMETER_VALUE / 2,
                    MAX_ACCELEROMETER_VALUE / 2,
                    MAX_ACCELEROMETER_VALUE / 2
            };
        }

        ThreeAxisAcceleration<int> getAcceleration() override {
            return acceleration;
        }

        void updateAcceleration(const int accelerationOnX,const  int accelerationOnY,const  int accelerationOnZ){
            acceleration.X = accelerationOnX;
            acceleration.Y = accelerationOnY;
            acceleration.Z = accelerationOnZ;
        }
    private:
        ThreeAxisAcceleration<int> acceleration;
    };
}

#endif //NUNCHUCKADAPTER_ACCELEROMETER_H
