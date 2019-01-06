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
     * Internally this class convert automatically the raw accelerometer integer values (10bit, range from 0 to 1023) into
     * the relative float "g" value (interval measured by the chip is between -2g an 2g)
     *
     * " The accelerometer chip is in the LIS3L02 series from STMicroelectronics.
     * The AE variant is not on their web site;"     *
     * reference (http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck)
     *
     * According to the Chipworks MEMS reports Dec-2010 (http://www.chipworks.com/Products/Chipworks_Latest%20MEMS%20Reports-Dec2010.pdf)
     * the device "STMicroelectronics 3-Axis Accelerometer (from Wii) LIS3L02AE" mounted on the Wii nunchuck is the descripted by
     * "The LIS3L02AL is a low-power 3-axis linear capacitive accelerometer that includes a sensing element and an IC interface"
     *
     * The class constant relative to the characteristics of the circuit is taken from the datasheet of the model LIS3L02AL
     *
     * */
    class NunchuckAccelerometer : ThreeAxisAccelerometer<float>{
    public:
        static const int MIN_ACCELEROMETER_VALUE = 0;
        static const int MAX_ACCELEROMETER_VALUE = 1023;

        static constexpr float referenceVoltage = 3.3;
        static constexpr float sensitivity = referenceVoltage/5;
        static constexpr float zeroGVoltage = referenceVoltage/2;
        static constexpr float conversionFactorRawToVolts = referenceVoltage/MAX_ACCELEROMETER_VALUE;

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
            return ((rawValue * conversionFactorRawToVolts) - zeroGVoltage)/sensitivity;
        }
    private:
        ThreeAxisAcceleration<float> acceleration;
    };
}

#endif //NUNCHUCKADAPTER_ACCELEROMETER_H
