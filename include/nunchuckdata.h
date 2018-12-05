//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKWIRINGPI_NUNCHUCK_DATA_H
#define NUNCHUCKWIRINGPI_NUNCHUCK_DATA_H

#include "threeaxisaccelerometer.h"
#include "joystick.h"

namespace nunchuckwiringpi {

    class NunchuckData{
    public:
        NunchuckData(NunchuckJoystick joystick, NunchuckAccelerometer accelerometer){
            this->joystick = joystick;
            this->accelerometer;
        }

        ThreeAxisAcceleration<int> getAccelerationValues() {
            return accelerometer.getAcceleration();
        }

        JoystickPosition<int> getJoystickPosition(){
            return joystick.getPosition();
        }
    private:
        NunchuckJoystick joystick;
        NunchuckAccelerometer accelerometer;
    };
}

#endif //NUNCHUCKWIRINGPI_NUNCHUCK_DATA_H
