# nunchuck-adapter

 This is a __header-only library__ that can be used to interact with the __Wii Nunchuck controller__ on a RaspberryPi.

* Internally this library use the WiringPi library in order to interact with the I2C bus. 

    * _Be sure if you have installed the WiringPi on your Raspberry_

* This library offers the possibility to simply read data from the Nunchuck

* If you need an entity that read continuosly data from the nunchuck, 
you can use directly an object of the _NunchuckDataSampler_ class. 
This class save nunchuck read data in a object of the thread safe _NunchuckDataStore_ class, 
from which they can be read from other threads.  

See the __main.cpp__ file in the __src__ directory for an usage example.