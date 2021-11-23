/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
#include "../I2CDevice.h"

namespace greenhouse {

//Inherit from the i2c helper class
class hih8120: protected exploringBB::I2CDevice {

public:
    // class variables
    unsigned int i2xc;
    float temperature;
    float humidity;

private:
    //Private functions and variables
    unsigned int I2CBus, I2CAddress;

    float map14bitValueHumidity(unsigned int value);
    float map14bitValueTemperature(unsigned int value);

public:
    //Functions for the user
	hih8120(unsigned int I2CBus, unsigned int I2CAddress=0x53);
    void readCurrentTemperatureHumidity();

}; // class

} // Namespace
