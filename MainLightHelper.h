#pragma once
#include "Arduino.h"
#include "BaseOnOfDeviceHelper.h"
#include "ClockHelper.h"
class MainLightHelper:
	public BaseOnOfDeviceHelper
{
	

private:
	MainLightHelper(){};
	MainLightHelper(MainLightHelper const&){};
	MainLightHelper& operator=(MainLightHelper const&){};
	static MainLightHelper* m_pInstance;

	long previousMillis = 0;
	uint8_t currentBright = 0;

protected:
	void HandleState();
public:
	bool IsFadeWasComplete = true;

	enum BrightLevel
	{
		Off = 0,
		Low = 127,
		Medium = 191,
		High = 255
	};

	BrightLevel CurrentLevel = Off;

	void loop();
	void Start();
	void Stop();
	void Toggle();

	void HandleDayPartChanged(ClockHelper::DayPart dayPart);
	
	static MainLightHelper* Instance();
};

