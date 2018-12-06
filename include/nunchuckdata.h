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
        NunchuckData(NunchuckJoystick joystick,
                NunchuckAccelerometer accelerometer,
                NunchuckButton buttonZ,
                NunchuckButton buttonC){
            this->joystick = joystick;
            this->accelerometer = accelerometer;
            this->buttonZ = buttonZ;
            this->buttonC = buttonC;
        }

        NunchuckData(): NunchuckData(NunchuckJoystick(),NunchuckAccelerometer(), NunchuckButton(), NunchuckButton()){};

        ThreeAxisAcceleration<int> getAccelerationValues() {
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
