#include "TimeHelper.h"
#include "Arduino.h"


TimeHelper::TimeHelper()
{
}

TimeHelper::TimeHelper(char* timeName)
{
	TimeName = timeName;
}


TimeHelper::~TimeHelper()
{
}

void TimeHelper::IncrementHours()
{
	Hours++;
	if (Hours > 23)
	{
		Hours = 0;
	}
};
void TimeHelper::DecrementHours()
{
	Hours--;
	if (Hours < 0)
	{
		Hours = 23;
	}
};
void TimeHelper::IncrementMinutes()
{
	Minutes++;
	if (Minutes > 59)
	{
		if (!isEditMode)
		{
			IncrementHours();
		}

		Minutes = 0;
	}


};
void TimeHelper::DecrementMinutes()
{
	Minutes--;
	if (Minutes < 0)
	{
		Minutes = 59;
	}
};

String TimeHelper::getFormatedTime()
{
	String hoursString = String(Hours);
	if (Hours < 10)
	{
		hoursString = String("0" + hoursString);
	}

	String minutesString = String(Minutes);
	if (Minutes < 10)
	{
		minutesString = String("0" + minutesString);
	}

	return String(hoursString + ":" + minutesString);
}

String TimeHelper::getFormatedHours()
{
	String hoursString = String(Hours);
	if (Hours < 10)
	{
		hoursString = String("0" + hoursString);
	}

	return String(hoursString);
}

String TimeHelper::getFormatedMinutes()
{
	String minutesString = String(Minutes);
	if (Minutes < 10)
	{
		minutesString = String("0" + minutesString);
	}

	return String(minutesString);
}
