#include <iostream>

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <raspberrypiutils.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<errno.h>
#include "nunchuck.h"

using namespace std;
using namespace nunchuckwiringpi;

int main() {
    int NUNCHUCK_DEVICE = 0x52;

    printf("Testing the nunchuck through I2C with the wiringPi Library\n");
    wiringPiSetup();
    try{
        Nunchuck nunchuck = Nunchuck();
        nunchuck.initWithoutEncryption();
        while(1){
            nunchuck.updateValues();
            cout << "Joystick pos: " << nunchuck
        }
    } catch(std::exception &ex)  {
        cerr << "ERROR: " << ex.what() << endl;
        exit(-1);
    }
    return 0;
}