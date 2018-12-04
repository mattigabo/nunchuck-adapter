//
// Created by Matteo Gabellini on 2018-12-04.
//

#ifndef NUNCHUCKWIRINGPI_NUNCHUCKOBSERVER_H
#define NUNCHUCKWIRINGPI_NUNCHUCKOBSERVER_H

#include <thread>
#include "nunchuck.h"

namespace nunchuckwiringpi{
    class NunchuckUpdater{
    public:
        NunchuckUpdater(Nunchuck* nunchuck){
            this->nunchuck = nunchuck;
            this->valueUpdater = std::thread(updateBehaviour, this);
        }

        void notifyStop(){
            shouldContinue = false;
        }
    private:
        Nunchuck* nunchuck;
        bool shouldContinue = true;
        std::thread valueUpdater;
        std::function<void(void)> updateBehaviour = [&]() {
            while(shouldContinue) {
                nunchuck->refreshValues();
            }
        };
    };
}

#endif //NUNCHUCKWIRINGPI_NUNCHUCKOBSERVER_H
