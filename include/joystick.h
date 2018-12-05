//
// Created by Matteo Gabellini on 2018-12-03.
//

#ifndef NUNCHUCKADAPTER_JOYSTICK_H
#define NUNCHUCKADAPTER_JOYSTICK_H

#include <mutex>

namespace nunchuckadapter {
    template<class T>
    struct JoystickPosition{
        T X;
        T Y;
    };

    template <class T>
    class Joystick{
        virtual JoystickPosition<T> getPosition() = 0;
    };

    class NunchuckJoystick: Joystick<int> {
    public:
        /*  According to http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck#Data_Format
         * "The values returned by the analog stick in the nunchuk enclosure do not encompass the full possible range,
         * but rather have upper and lower bounds. These bounds seem to be in the same range across Nunchuks,
         * but there is some variation. Analog stick X returns data from around 35 (fully left) to 228(fully right),
         * while analog stick Y returns from around 27 to 220. Center for both is around 128."
        */
        static const int CLASSIC_NUNCHUCK_FULLY_LEFT_X_VALUE = 35;
        static const int CLASSIC_NUNCHUCK_FULLY_RIGHT_X_VALUE = 228;
        static const int CLASSIC_NUNCHUCK_FULLY_UP_Y_VALUE = 27;
        static const int CLASSIC_NUNCHUCK_FULLY_DOWN_X_VALUE = 220;
        static constexpr JoystickPosition<int> GET_CLASSIC_NUNCHUCK_CENTER_VALUE() { return {.X = 128, .Y = 128}; };

        NunchuckJoystick(const int x,const  int y) {
            position = { x, y };
        }

        NunchuckJoystick() {
            position = NunchuckJoystick::GET_CLASSIC_NUNCHUCK_CENTER_VALUE();
        }

        JoystickPosition<int> getPosition() override {
            return position;
        }

        void updatePosition(const int x, const int y){
            position.X = x;
            position.Y = y;
        }
    private:
        JoystickPosition<int> position;
    };
}

#endif //NUNCHUCKADAPTER_JOYSTICK_H
