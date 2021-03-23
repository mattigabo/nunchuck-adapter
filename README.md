# nunchuck-adapter

 This is a __header-only library__ that can be used to interact with the __Wii Nunchuck controller__ on a RaspberryPi.

* Internally this library uses the WiringPi library in order to interact with the I2C bus. 

    * _Make sure you have installed WiringPi on your Raspberry_

* This library offers the possibility to simply read data from the Nunchuck

* If you need an entity that continuously reads data from the nunchuck, 
you can directly use an object of the _NunchuckDataSampler_ class. 
This class saves the data read by the nunchuck in an object of the thread safe class called _NunchuckDataStore_, 
from which they can be read from other threads.  

See the __main.cpp__ file in the __src__ directory for an usage example.
