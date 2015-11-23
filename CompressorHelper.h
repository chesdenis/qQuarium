#pragma once
#include "Arduino.h"
#include "BaseOnOfDeviceHelper.h"
#include "ClockHelper.h"
class CompressorHelper :
	public BaseOnOfDeviceHelper
{
private:
	CompressorHelper(){};
	CompressorHelper(CompressorHelper const&){};
	CompressorHelper& operator=(CompressorHelper const&){};
	static CompressorHelper* m_pInstance;

public:
	static CompressorHelper* Instance();
	void HandleDayPartChanged(ClockHelper::DayPart dayPart);
};

