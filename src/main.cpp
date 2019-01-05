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



void printRawData(RawNunchuckData rawData){
    cout << " Joystick: [ " <<
         rawData.joystickPositionX << " X, " <<
         rawData.joystickPositionY << " Y ]" <<
         "\n Accelerometer: [ " <<
         rawData.accelerationOnX << " X,  " <<
         rawData.accelerationOnY << " Y,  " <<
         rawData.accelerationOnZ << " Z ]" <<
         "\n ButtonZ state " << rawData.buttonZState <<
         " ButtonC state " << rawData.buttonCState << endl;
}

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
    cout << "-----------------------------------------------" << endl;
    try{
        auto reader = new NunchuckReader(NunchuckReader::InitializationMode::NOT_ENCRYPTED);

        cout << "-----------------------------------------------" << endl;

        cout << "Test read RAW DATA" << endl;
        for(int i = 0; i < 20;  i++){
            RawNunchuckData values = reader->readRawData();
            printRawData(values);
            std::this_thread::sleep_for(chrono::milliseconds(500));
        }
        cout << "-----------------------------------------------" << endl;
        cout << "-----------------------------------------------" << endl;

        cout << "Test read directly from the main thread" << endl;
        cout << "Value sampled by the Main Thread " << endl;
        for(int i = 0; i < 20;  i++){
            NunchuckData values = reader->readDeviceValues();
            printData(values);
            std::this_thread::sleep_for(chrono::milliseconds(500));
        }

        cout << "-----------------------------------------------" << endl;
        cout << "Test read from the NunchuckDataSampler thread" << endl;
        cout << "Value sampled by a NunchuckDataSampler" << endl;
        auto dataStore = new NunchuckDataStore();
        auto sampler = new NunchuckDataSampler(reader, dataStore);
        for(int i = 0; i < 20;  i++){
            NunchuckData values = dataStore->fetch();
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