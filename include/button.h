//
// Created by Matteo Gabellini on 2018-12-05.
//

#ifndef NUNCHUCKADAPTER_BUTTON_H
#define NUNCHUCKADAPTER_BUTTON_H

namespace nunchuckadapter{
    class Button{
    public:
        explicit Button(const bool initialState){
            is_pressed = initialState;
        }
        bool isPressed(){
            return is_pressed;
        }
    protected:
        bool is_pressed;
    };

    class NunchuckButton: Button{
    public:
        NunchuckButton(): Button(false){
        }

        explicit NunchuckButton(const int buttonValue): Button(false){
            this->setState(buttonValue);
        }

        /**
         * Set the nunchuck button state.
         * According to the documentation at
         * http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck#Data_Format
         * the Nunchuck button is pressed when is value is 0
         * */
        void setState(int valueRead){
            is_pressed = valueRead == 0;
        }
    };
}

#endif //NUNCHUCKADAPTER_BUTTON_H
