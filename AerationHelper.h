#pragma once
#include "Arduino.h"
#include "BaseOnOfDeviceHelper.h"
#include "ClockHelper.h"
class AerationHelper:
	public BaseOnOfDeviceHelper
{
private:
	AerationHelper(){};
	AerationHelper(AerationHelper const&){};
	AerationHelper& operator=(AerationHelper const&){};
	static AerationHelper* m_pInstance;

public:	
	static AerationHelper* Instance();

	void HandleDayPartChanged(ClockHelper::DayPart dayPart);
};

