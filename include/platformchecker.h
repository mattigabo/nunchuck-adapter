//
// Created by Matteo Gabellini on 2018-12-05.
//

#ifndef NUNCHUCKADAPTER_PLATFORMCHECKER_H
#define NUNCHUCKADAPTER_PLATFORMCHECKER_H

/*
* To date, this is the only mode that I found in order to distinguish the RaspberryPi architecture
* from other typical notebook computer architectures through the precompiler directives.
* If I find another way in the future, I will probably change the following check.
* */
#ifdef __arm__

#define __RASPBERRYPI_PLATFORM__

#endif

#endif //NUNCHUCKADAPTER_PLATFORMCHECKER_H
