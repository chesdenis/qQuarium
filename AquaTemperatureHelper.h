#pragma once
#include "Arduino.h"
#include "OneWire.h"

class AquaTemperatureHelper
{
private:
	AquaTemperatureHelper(){};
	AquaTemperatureHelper(AquaTemperatureHelper const&){};
	AquaTemperatureHelper& operator=(AquaTemperatureHelper const&){};
	static AquaTemperatureHelper* m_pInstance;

	uint8_t tempAnalog = 0;
	float currentTempValue = 0;

	long lastTempShortUpdatedTime = 0;
	byte data[12];
	unsigned int raw;

	OneWire oneWire = NULL;

	
public:
	void ReadTemperature();
	void setup(uint8_t tempSensorPinNum);
	
	bool isAquaVeryCold = false;
	bool isAquaVeryHeat = false;
	bool isAquaNorm = false;
	
	int minAquaTemp = 20;
	int maxAquaTemp = 30;
	
	static AquaTemperatureHelper* Instance();

	String GetTemperatureText();
	int GetTemperatureValue();

	void loop();

	void IncreaseMinTemp();
	void DecreaseMinTemp();
	void IncreaseMaxTemp();
	void DecreaseMaxTemp();
};

