#pragma once
#include "LiquidCrystal.h"


class LcdBackLightHelper
{
private:
	LcdBackLightHelper(){};
	LcdBackLightHelper(LcdBackLightHelper const&){};
	LcdBackLightHelper& operator=(LcdBackLightHelper const&){};
	static LcdBackLightHelper* m_pInstance;

	bool isStateWasUpdated = false;
	int AutoOffCounter = 0; // 10 sec
	unsigned long previousMillis = 0;

	uint8_t LcdBackLightPinNum = 0;

public:
	static LcdBackLightHelper* Instance();

	void init(uint8_t lcdBackLightPinNum);
	void loop();
	void IncreaseLedTime();
};

