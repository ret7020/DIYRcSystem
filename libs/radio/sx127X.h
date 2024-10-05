/*
This driver use this library: https://github.com/sandeepmistry/arduino-LoRa/tree

So it will work with any device supported by lib.
*/

#include "LoRa.h"


class SX127XRadio{
    public:
        LoRaClass device = LoRaClass();

        SX127XRadio(long frequency)
        {
            init(long frequency);
        }
        
        void init(){
            if (!device.begin()){} // Radio error
        }
};