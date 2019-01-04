#include <iostream>

#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<cerrno>

#ifdef  __RASPBERRYPI_PLATFORM__
#include <wiringPi.h>
#else
#include "mockedwiringpi.h"
#endif

#include "nunchuckdata.h"
#include "nunchuckreader.h"
#include "nunchuckdatasampler.h"

using namespace std;
using namespace nunchuckadapter;

void printData(NunchuckData values){
    cout << " Joystick: [ " <<
         values.getJoystickPosition().X << " X, " <<
         values.getJoystickPosition().Y << " Y ]" <<
         "\n Accelerometer: [ " <<
         values.getAccelerationValues().X << " in g on X,  " <<
         values.getAccelerationValues().Y << " in g on Y,  " <<
         values.getAccelerationValues().Z << " in g on Z ]" <<
         "\n ButtonZ is pressed? " << (values.getButtonZ().isPressed() ? "TRUE" : "FALSE") <<
         " ButtonC is pressed? " << (values.getButtonC().isPressed() ? "TRUE" : "FALSE") << endl;
}

int main() {
    int NUNCHUCK_DEVICE = 0x52;

    cout << "Testing the nunchuck through I2C with the wiringPi Library" << endl;
    wiringPiSetup();
    try{
        cout << "Test read directly from the main thread" << endl;
        auto reader = new NunchuckReader(NunchuckReader::InitializationMode::NOT_ENCRYPTED);
        for(int i = 0; i < 20;  i++){
            NunchuckData values = reader->readDeviceValues();
            cout << "Value sampled by the Main Thread " << endl;
            printData(values);
        }

        cout << "-----------------------------------------------" << endl;
        cout << "Test read from the NunchuckDataSampler thread" << endl;
        auto dataStore = new NunchuckDataStore();
        auto sampler = new NunchuckDataSampler(reader, dataStore);
        for(int i = 0; i < 20;  i++){
            NunchuckData values = dataStore->fetch();
            cout << "Value sampled by a NunchuckDataSampler" << endl;
            printData(values);
            std::this_thread::sleep_for(chrono::milliseconds(1000));
        }

        cout << "-----------------------------------------------" << endl;
        cout << "Notify stop to the sampler..." << endl;
        sampler->notifyStop();
        cout << "Wait the sampler termination..." << endl;
        sampler->join();

        cout << "-----------------------------------------------" << endl;
        cout << "Bye Bye" << endl;
        free(sampler);
        free(dataStore);
        free(reader);
    } catch(std::exception &ex)  {
        cerr << "ERROR: " << ex.what() << endl;
        exit(-1);
    }
    return 0;
}