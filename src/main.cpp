#include <iostream>

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <raspberrypiutils.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<errno.h>
#include "nunchuckdata.h"
#include "nunchuckreader.h"
#include "nunchuckdatasampler.h"

using namespace std;
using namespace nunchuckadapter;

int main() {
    int NUNCHUCK_DEVICE = 0x52;

    cout << "Testing the nunchuck through I2C with the wiringPi Library" << endl;
    wiringPiSetup();
    try{
        cout << "Test read directly from the main thread" << endl;
        NunchuckReader nunchuckReader = NunchuckReader(NunchuckReader::InitializationMode::NOT_ENCRYPTED);
        for(int i = 0; i < 100;  i++){
            NunchuckData values = nunchuckReader.readDeviceValues();
            cout << "Joystick pos: " << values.getJoystickPosition().X;
        }

        cout << "Test read from the NunchuckDataSampler thread" << endl;
        NunchuckDataStore dataStore = NunchuckDataStore();
        NunchuckDataSampler updater = NunchuckDataSampler(&nunchuckReader, &dataStore);
        for(int i = 0; i < 100;  i++){
            NunchuckData values = dataStore.fetch();
            cout << "Joystick pos: " << values.getJoystickPosition().X;
            std::this_thread::sleep_for(chrono::milliseconds(1500));
        }

    } catch(std::exception &ex)  {
        cerr << "ERROR: " << ex.what() << endl;
        exit(-1);
    }
    return 0;
}