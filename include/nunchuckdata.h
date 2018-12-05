//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCK_ADAPTER_NUNCHUCK_DATA_H
#define NUNCHUCK_ADAPTER_NUNCHUCK_DATA_H

#include "threeaxisaccelerometer.h"
#include "joystick.h"

namespace nunchuckadapter {

    class NunchuckData{
    public:
        NunchuckData(NunchuckJoystick joystick, NunchuckAccelerometer accelerometer){
            this->joystick = joystick;
            this->accelerometer = accelerometer;
        }

        NunchuckData(){
            NunchuckData(NunchuckJoystick(),NunchuckAccelerometer());
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

#endif //NUNCHUCK_ADAPTER_NUNCHUCK_DATA_H
