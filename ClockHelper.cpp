#include "ClockHelper.h"
#include "Arduino.h"
#include "WString.h"

ClockHelper* ClockHelper::m_pInstance = NULL;
ClockHelper* ClockHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new ClockHelper;

	return m_pInstance;
}

String ClockHelper::GetIntValAsTwoChars(uint8_t valToPrint)
{
	String retVal = String(valToPrint);
	return retVal;
}

String ClockHelper::GetYearNum(uint16_t year)
{
	String yearString = String(year);

	return yearString;
}


String ClockHelper::GetCurrentTimeFormatedDate()
{
	Clock.getTime();

	String dayString = String(Clock.dayOfMonth);
	if (Clock.dayOfMonth < 10)
	{
		dayString = String("0" + dayString);
	}

	String monthString = String(Clock.month);
	if (Clock.month < 10)
	{
		monthString = String("0" + monthString);
	}

	String yearString = String(Clock.year + 2000);

	return String(dayString + "." + monthString + "." + yearString);

};
String ClockHelper::GetCurrentTimeFormatedTime()
{
	Clock.getTime();

	String hoursString = String(Clock.hour);
	if (Clock.hour < 10)
	{
		hoursString = String("0" + hoursString);
	}

	String minutesString = String(Clock.minute);
	if (Clock.minute < 10)
	{
		minutesString = String("0" + minutesString);
	}

	return String(hoursString + ":" + minutesString);
};
String ClockHelper::GetCurrentTimeFormatedDay()
{
	Clock.getTime();
	
	uint8_t currentDay = Clock.dayOfWeek;
	
	switch (currentDay)
	{
	case 1:return String("Mo");
		break;
	case 2:return String("Tu");
		break;
	case 3:return String("We");
		break;
	case 4:return String("Th");
		break;
	case 5:return String("Fr");
		break;
	case 6:return String("Sa");
		break;
	case 7:return String("Su");
		break;
	default:
		return String("");
	}
};

String ClockHelper::GetFormatedDayLong(uint8_t dayOfWeek)
{
	switch (dayOfWeek)
	{
	case 1:return String("Monday");
		break;
	case 2:return String("Tuesday");
		break;
	case 3:return String("Wednesday");
		break;
	case 4:return String("Thursday");
		break;
	case 5:return String("Friday");
		break;
	case 6:return String("Saturday");
		break;
	case 7:return String("Sunday");
		break;
	default:
		return String("");
	}
}
bool ClockHelper::isTimeBeetwenTimes(
	int timeToCompareHours,
	int timeToCompareMinutes,
	int time1Hours,
	int time1Minutes,
	int time2Hours,
	int time2Minutes)
{
	long time1TotalMinutes = time1Hours * 60 + time1Minutes;
	long time2TotalMinutes = time2Hours * 60 + time2Minutes;

	long timeToCompareTotalMinutes = timeToCompareHours * 60 + timeToCompareMinutes;

	if (time1TotalMinutes > time2TotalMinutes)
	{
		// example: t1= 22:30, t2=00:30, so 23:30 is beetween t1 and t2.

		if (timeToCompareTotalMinutes <= time2TotalMinutes)
		{
			//example:  t1= 22:30, t2=02:30, 01:13 is low than 2:30.
			return true;
		}
		else if (timeToCompareTotalMinutes >= time1TotalMinutes)
		{
			//example: t1= 22:30, t2=02:30, 23:13 is high than 22:30, but is also high than 02:30.
			return true;
		}
	}
	else
	{
		// example: t1=02:15, t2=3:15, so 2:45 is beetween t1 and t2

		if (timeToCompareTotalMinutes >= time1TotalMinutes && timeToCompareTotalMinutes <= time2TotalMinutes)
		{
			return true;
		}
	}

	return false;
}

ClockHelper::DayPart ClockHelper::GetDayPart()
{
	int currentTimeHours = Clock.hour;
	int currentTimeMinutes = Clock.minute;

	int morningOnHours = MorningOn.Hours;
	int morningOnMinutes = MorningOn.Minutes;

	int dayOnHours = DayOn.Hours;
	int dayOnMinutes = DayOn.Minutes;

	int eveningOnHours = EveningOn.Hours;
	int eveningOnMinutes = EveningOn.Minutes;

	int nightOnHours = NightOn.Hours;
	int nightOnMinutes = NightOn.Minutes;

	int morningOffHours = dayOnHours;
	int morningOffMinutes = dayOnMinutes;

	int dayOffHours = eveningOnHours;
	int dayOffMinutes = eveningOnMinutes;

	int eveningOffHours = nightOnHours;
	int eveningOffMinutes = nightOnMinutes;

	int nightOffHours = morningOnHours;
	int nightOffMinutes = morningOnMinutes;

	if (isTimeBeetwenTimes(Clock.hour, Clock.minute, 
		MorningOn.Hours, MorningOn.Minutes, 
		DayOn.Hours, DayOn.Minutes))
	{
		return ClockHelper::Morning;
	}

	if (isTimeBeetwenTimes(Clock.hour, Clock.minute,
		DayOn.Hours, DayOn.Minutes,
		EveningOn.Hours, EveningOn.Minutes))
	{
		return ClockHelper::Day;
	}

	if (isTimeBeetwenTimes(Clock.hour, Clock.minute,
		EveningOn.Hours, EveningOn.Minutes,
		NightOn.Hours, NightOn.Minutes))
	{
		return ClockHelper::Evening;
	}

	if (isTimeBeetwenTimes(Clock.hour, Clock.minute,
		NightOn.Hours, NightOn.Minutes,
		MorningOn.Hours, MorningOn.Minutes))
	{
		return ClockHelper::Night;
	}

	return Night;
};



void ClockHelper::loop()
{
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis > timerUpdateInterval) {
		previousMillis = currentMillis;
		isUpdatedByTimer = false;
	}
}