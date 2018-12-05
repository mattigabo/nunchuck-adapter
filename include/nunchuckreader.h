//
// Created by Matteo Gabellini on 2018-12-05.
//

#ifndef NUNCHUCKWIRINGPI_NUNCHUCKREADER_H
#define NUNCHUCKWIRINGPI_NUNCHUCKREADER_H

#include "nunchuckdata.h"

#include<wiringPi.h>
#include<wiringPiI2C.h>

namespace nunchuckwiringpi{

    /*
    * This class encapsulate the interaction with Nunchuck and the relative I2C protocol management.
    * */
    class NunchuckReader {
    public:
        enum InitializationMode {
            ENCRYPTED,
            NOT_ENCRYPTED
        };
        static const int NUNCHUCK_I2C_ADDRESS = 0x52;
        static const int MINIMUN_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS = 300;
        static const int DEFAULT_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS = 500;

        NunchuckReader(int circuitAdaptationWaitMicrosecons, InitializationMode initializationMode){
            if(circuitAdaptationWaitMicrosecons < MINIMUN_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS){
                throw "The minimun circuit adapdation wait time is " + Nunchuck::MINIMUN_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS + " microseconds. Please specify a value less than" + Nunchuck::MINIMUN_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS;
            }
            this->circuitAdaptationWaitMicrosecons = circuitAdaptationWaitMicrosecons;

            initI2C();

            switch (initializationMode){
                case InitializationMode::ENCRYPTED:
                    initWithEncryption();
                    break;
                case InitializationMode::NOT_ENCRYPTED:
                    initWithoutEncryption();
                    break;
                default:
                    throw "Invalid initialization mode";
                    break;
            }
        }

        NunchuckReader(InitializationMode initializationMode){
            NunchuckReader(NunchuckReader::DEFAULT_CIRCUIT_ADAPTATION_WAIT_MICROSECONDS, initializationMode);
        }

        bool isEncryptedModeEnabled() {
            return encyptedModeEnabled;
        }

        void initI2C(){
            i2CPortFileDescriptor = wiringPiI2CSetup(NunchuckReader::NUNCHUCK_I2C_ADDRESS);
            if (i2CPortFileDescriptor < 0) {
                throw "Error during the setup of the I2C communication with the Nunchuck";
            }
        }

        void initWithEncryption(){
            wiringPiI2CWriteReg8(i2CPortFileDescriptor, 0x40, 0x00);
            delayMicroseconds(circuitAdaptationWaitMicrosecons);
            encyptedModeEnabled = true;
        }

        void initWithoutEncryption(){
            wiringPiI2CWriteReg8(i2CPortFileDescriptor, 0xF0, 0x55);
            wiringPiI2CWriteReg8(i2CPortFileDescriptor, 0xFB, 0x00);
            delayMicroseconds(circuitAdaptationWaitMicrosecons);
            encyptedModeEnabled = false;
        }

        /*
         * Read the values of the nunchuck
         * @return an NunchuckData object that contains the data
         * read from the device
         * */
        NunchuckData readDeviceValues(){
            int readBuffer[6];
            readRawData(readBuffer);

            int joyX = readBuffer[0];
            int joyY = readBuffer[1];
            NunchuckJoystick joystick = NunchuckJoystick(joyX, joyY);

            int accelX = (readBuffer[2] << 2) | ((readBuffer[5] & 0xc0) >> 6);
            int accelY = (readBuffer[3] << 2) | ((readBuffer[5] & 0x30) >> 4);
            int accelZ = (readBuffer[4] << 2) | ((readBuffer[5] & 0x0c) >> 2);
            NunchuckAccelerometer accelerometer = NunchuckAccelerometer(accelX, accelY, accelZ);

            int c = (readBuffer[5] & 0x02) >> 1;
            int z = readBuffer[5] & 0x01;

            return NunchuckData(joystick, accelerometer);
        };
    private:
        bool encyptedModeEnabled;
        int i2CPortFileDescriptor;
        int circuitAdaptationWaitMicrosecons;


        /*
         * Decryption function for bytes read from the Nunchuck when
         * it is inizialized with the encryption mode
         * */
        int decrypt(int readByte){
            return (readByte ^ 0x17) + 0x17;
        }

        void readRawData(int *readBuffer) {
            wiringPiI2CWrite(fd, 0x00);
            delayMicroseconds(circuitAdaptationWaitMicrosecons);

            int i;
            for (i=0; i<6; i++) {
                readBuffer[i] = wiringPiI2CRead(fd);
            }
        };

    };
}

#endif //NUNCHUCKWIRINGPI_NUNCHUCKREADER_H
