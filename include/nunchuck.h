//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKWIRINGPI_NUNCHUCK_H
#define NUNCHUCKWIRINGPI_NUNCHUCK_H


#include "threeAxisAccelerometer.hpp"

namespace nunchuckwiringpi {

    class NunchuckAccelerometer : ThreeAxisAccelerometer<int>{
    public:
        NunchuckAccelerometer();
        ThreeAxisAcceleration<int> getAcceleration() {
            return acceleration;
        }
        void updateAcceleration(int accelerationOnX, int accelerationOnY, int accelerationOnZ){
            acceleration.X = accelerationOnX;
            acceleration.Y = accelerationOnY;
            acceleration.Z = accelerationOnZ;
        }
    private:
        ThreeAxisAcceleration<int> acceleration;
    };

    class nunchuck: ThreeAxisAccelerometer<int>{
    public:
        static const int NUNCHUCK_I2C_ADDRESS = 0x52;
        nunchuck();
        ThreeAxisAcceleration<int> getAccelerometerValues();
    private:
        int register[6];
        NunchuckAccelerometer accelerometer;
    };
}

#endif //NUNCHUCKWIRINGPI_NUNCHUCK_H
