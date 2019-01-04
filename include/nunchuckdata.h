//
// Created by Matteo Gabellini on 2018-11-29.
//

#ifndef NUNCHUCKADAPTER_NUNCHUCK_DATA_H
#define NUNCHUCKADAPTER_NUNCHUCK_DATA_H

#include "threeaxisaccelerometer.h"
#include "joystick.h"
#include "button.h"

namespace nunchuckadapter {

    class NunchuckData{
    public:
        NunchuckData(NunchuckJoystick joystick = NunchuckJoystick(),
                NunchuckAccelerometer accelerometer = NunchuckAccelerometer(),
                NunchuckButton buttonZ = NunchuckButton(),
                NunchuckButton buttonC = NunchuckButton()){
            this->joystick = std::move(joystick);
            this->accelerometer = std::move(accelerometer);
            this->buttonZ = buttonZ;
            this->buttonC = buttonC;
        }

        ThreeAxisAcceleration<float> getAccelerationValues() {
            return accelerometer.getAcceleration();
        }

        JoystickPosition<int> getJoystickPosition(){
            return joystick.getPosition();
        }

        Button getButtonZ(){
            return buttonZ;
        }

        Button getButtonC(){
            return buttonC;
        }
    private:
        NunchuckJoystick joystick;
        NunchuckAccelerometer accelerometer;
        NunchuckButton buttonZ;
        NunchuckButton buttonC;
    };
}

#endif //NUNCHUCKADAPTER_NUNCHUCK_DATA_H
