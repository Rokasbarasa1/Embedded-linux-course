#include "../I2CDevice.h"

namespace greenhouse {

class hih8120: protected exploringBB::I2CDevice {

public:
    unsigned int i2xc;
    float temperature;
    float humidity;

private:
    unsigned int I2CBus, I2CAddress;

    float map14bitValueHumidity(unsigned int value);
    float map14bitValueTemperature(unsigned int value);

public:
	hih8120(unsigned int I2CBus, unsigned int I2CAddress=0x53);
    void readCurrentTemperatureHumidity();

}; // class

} // Namespace
