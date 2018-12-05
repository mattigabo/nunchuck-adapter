//
// Created by Matteo Gabellini on 2018-12-04.
//

#ifndef NUNCHUCK_ADAPTER_NUNCHUCKOBSERVER_H
#define NUNCHUCK_ADAPTER_NUNCHUCKOBSERVER_H

#include <thread>
#include "nunchuckdata.h"
#include "nunchuckreader.h"

namespace nunchuckadapter{
    /*
     * This class represent a thread safe structure where a NunchuckUpdater store data
     * read from the device and expose a function to read the stored data
     * */
    class NunchuckDataStore{
    public:
        NunchuckDataStore(){
            this->nunchuckData = NunchuckData();
        }
        void store(NunchuckData data){
            std::lock_guard <std::mutex> lock(internal_mutex);
            this->nunchuckData = data;
        }

        NunchuckData fetch(){
            std::lock_guard <std::mutex> lock(internal_mutex);
            return nunchuckData;
        }
    private:
        NunchuckData nunchuckData;
        std::mutex internal_mutex;
    };


    /*
     * This class encapsulate the management of an autonomous thread
     * that read continuously data from the Nunchuck and put the read data in a
     * NunchuckDataStore object
     * */
    class NunchuckUpdater{
    public:
        NunchuckUpdater(NunchuckReader* deviceReader, NunchuckDataStore* dataStore){
            this->nunchuckReader = deviceReader;
            this->valueUpdater = std::thread(updateBehaviour, this);
        }

        void notifyStop(){
            shouldContinue = false;
        }
    private:
        NunchuckReader* nunchuckReader;
        NunchuckDataStore* dataStore;
        bool shouldContinue = true;
        std::thread valueUpdater;
        std::function<void(void)> updateBehaviour = [&]() {
            while(shouldContinue) {
                dataStore->store(nunchuckReader->readDeviceValues());
            }
        };
    };
}

#endif //NUNCHUCK_ADAPTER_NUNCHUCKOBSERVER_H
