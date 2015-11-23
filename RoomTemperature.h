#pragma once
#include "dht11.h"

class RoomTemperature
{
private:
	RoomTemperature(){};
	RoomTemperature(RoomTemperature const&){};
	RoomTemperature& operator=(RoomTemperature const&){};
	static RoomTemperature* m_pInstance;

	
	uint8_t TempAnalog = 0;
	uint8_t HumidityAnalog = 0;
	// создаём объект-сенсор
	dht11 DHT;
	uint8_t SensorPinNum;

public:
	
	String GetTemperatureText();
	String GetHumidityText();

	void ReadTemperature();
	void setup(uint8_t sensorPinNum);

	static RoomTemperature* Instance();

	void loop();
};

