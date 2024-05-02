/**
 * @author Rokas Barasa (285047@via.dk)
 * @author Arturas Maziliauskas (285051@via.dk)
 * @date 2021-11-23
 */
namespace greenhouse {

class photoresistor {

public:
    float lightLevel;

private:
    unsigned int I2CBus, I2CAddress;

    float mapVoltsToPercentage(unsigned int value);

public:
	photoresistor(unsigned int I2CBus);
    void readCurrentLightLevel();

}; // class

} // Namespace
