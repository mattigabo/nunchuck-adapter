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

    /**
     * This class represents the accelerometer of the Nunchuck.
     * Internally this class convert automatically the raw accelerometer integer values (range from 0 to 1023) into
     * the relative float "g" value (interval measured by the chip is between -2g an 2g)
     * */
    class NunchuckAccelerometer : ThreeAxisAccelerometer<float>{
    public:
        static const int MIN_ACCELEROMETER_VALUE = 0;
        static const int MAX_ACCELEROMETER_VALUE = 1023;
        static constexpr float MIN_G_MEASURED = 0 - 2.0; // -2g
        static constexpr float MAX_G_MEASURED = 2.0; // 2g
        static constexpr float conversionFactorRawToG = ((MAX_G_MEASURED - MIN_G_MEASURED)/(MAX_ACCELEROMETER_VALUE - MIN_ACCELEROMETER_VALUE));

        NunchuckAccelerometer(const int rawAccelerationOnX,const  int rawAccelerationOnY,const  int rawAccelerationOnZ){
            acceleration = {
                    convertRawValueToG(rawAccelerationOnX),
                    convertRawValueToG(rawAccelerationOnY),
                    convertRawValueToG(rawAccelerationOnZ)
            };
        }

        NunchuckAccelerometer(const float accelerationOnX,const float accelerationOnY,const float accelerationOnZ){
            acceleration = {
                    accelerationOnX,
                    accelerationOnY,
                    accelerationOnZ
            };
        }

        NunchuckAccelerometer() {
            acceleration = { 0.0, 0.0, 0.0 };
        }

        ThreeAxisAcceleration<float> getAcceleration() override {
            return acceleration;
        }

        void updateAcceleration(const int rawAccelerationOnX,const  int rawAccelerationOnY,const  int rawAccelerationOnZ){
            acceleration.X = convertRawValueToG(rawAccelerationOnX);
            acceleration.Y = convertRawValueToG(rawAccelerationOnY);
            acceleration.Z = convertRawValueToG(rawAccelerationOnZ);
        }

        void updateAcceleration(const float accelerationOnX, const float accelerationOnY, const float accelerationOnZ){
            acceleration.X = accelerationOnX;
            acceleration.Y = accelerationOnY;
            acceleration.Z = accelerationOnZ;
        }

        static float convertRawValueToG(int rawValue){
            return rawValue * conversionFactorRawToG + MIN_G_MEASURED;
        }
    private:
        ThreeAxisAcceleration<float> acceleration;
    };
}

#endif //NUNCHUCKADAPTER_ACCELEROMETER_H
