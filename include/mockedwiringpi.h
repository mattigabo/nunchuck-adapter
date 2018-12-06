//
// Created by Matteo Gabellini on 2018-12-05.
//

#ifndef NUNCHUCKADAPTER_MOCKEDWIRINGPI_H
#define NUNCHUCKADAPTER_MOCKEDWIRINGPI_H

#include "platformchecker.h"

#ifndef __RASPBERRYPI_PLATFORM__

/**
 * In this file can be found mocked implementation of the WiringPi function used in other project file.
 * These functions are used for code testing purposes on another platform for which the WiringPi library is not available
 * */
#include <iostream>
#include <cstdlib>

namespace  nunchuckadapter {

    struct MockedWiringPiI2C {
        int i2CFileDescriptor;
    };

    MockedWiringPiI2C mockedI2C = {42};

    void wiringPiSetup() {
        std::cout << "Set up function of the WiringPi Library Called" << std::endl;
    }

    int wiringPiI2CSetup(int deviceAddress) {
        return mockedI2C.i2CFileDescriptor;
    }

    void wiringPiI2CWriteReg8(int i2CPortFileDescriptor, int deviceAddress, int data) {
        std::cout <<
                  "Write on i2c port > Device Address " << deviceAddress <<
                  " Data: " << data
                  << std::endl;
    }

    void wiringPiI2CWrite(int i2CPortFileDescriptor, int data) {
        //std::cout << "Write on i2c port > Data: " << data << std::endl;
    }

    int wiringPiI2CRead(int i2CPortFileDescriptor) {
        return rand() % 256;
    }
}

#endif //__RASPBERRYPI_PLATFORM__

#endif //NUNCHUCKADAPTER_MOCKEDWIRINGPI_H
