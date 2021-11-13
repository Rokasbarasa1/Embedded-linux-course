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
