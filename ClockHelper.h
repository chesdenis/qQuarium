#pragma once
#include "WString.h"
#include "TimeHelper.h"
#include "DS1307.h"

class ClockHelper
{
	
private:
	ClockHelper(){};
	ClockHelper(ClockHelper const&){};
	ClockHelper& operator=(ClockHelper const&){};
	static ClockHelper* m_pInstance;

	unsigned long previousMillis = 0;
	
	bool isTimeBeetwenTimes(
		int timeToCompareHours,
		int timeToCompareMinutes,
		int time1Hours,
		int time1Minutes,
		int time2Hours,
		int time2Minutes);
public:
	long timerUpdateInterval = 60000; //default 60 sec, but in alert mode interval will decrease;
	
	DS1307 Clock;
	String GetCurrentTimeFormatedDate();
	String GetCurrentTimeFormatedTime();
	String GetCurrentTimeFormatedDay();
	String GetFormatedDayLong(uint8_t dayOfWeek);
	
	
	String GetYearNum(uint16_t year);

	
	String GetIntValAsTwoChars(uint8_t valToPrint);
	
	enum DayPart
	{
		Morning,
		Day,
		Evening,
		Night
	};

	TimeHelper MorningOn = TimeHelper("Morning ON:");
	TimeHelper DayOn = TimeHelper("Day ON:");
	TimeHelper EveningOn = TimeHelper("Evening ON:");
	TimeHelper NightOn = TimeHelper("Night ON:");
	
	bool isUpdatedByTimer = false;
		
	static ClockHelper* Instance();

	void loop();

	DayPart GetDayPart();
	
};

