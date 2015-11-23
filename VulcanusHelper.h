#include "Arduino.h"
#include "BaseOnOfDeviceHelper.h"
#include "ClockHelper.h"
#pragma once
class VulcanusHelper :
	public BaseOnOfDeviceHelper
{
private:
	VulcanusHelper(){};
	VulcanusHelper(VulcanusHelper const&){};
	VulcanusHelper& operator=(VulcanusHelper const&){};
	static VulcanusHelper* m_pInstance;
	
	long time = 0;
	int periode = 10000;
	
protected:
	void HandleState();

public:
	void loop();
	static VulcanusHelper* Instance();
	void HandleDayPartChanged(ClockHelper::DayPart dayPart);
};
