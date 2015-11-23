#include "VulcanusHelper.h"
VulcanusHelper* VulcanusHelper::m_pInstance = NULL;
VulcanusHelper* VulcanusHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new VulcanusHelper;

	return m_pInstance;
}

void VulcanusHelper::loop()
{
	VulcanusHelper::HandleState();
}


void VulcanusHelper::HandleState()
{
	if (IsActive){
		time = millis();
		int value = 160 + 95 * cos(2 * PI / periode*time);

		analogWrite(PinNum, value);
	}
	else
	{
		analogWrite(PinNum, 0);
	}
}

void VulcanusHelper::HandleDayPartChanged(ClockHelper::DayPart dayPart)
{
	switch (dayPart)
	{
	case ClockHelper::Morning:
		Stop();
		break;
	case ClockHelper::Day:
		Stop();
		break;
	case ClockHelper::Evening:
		Start();
		break;
	case ClockHelper::Night:
		Stop();
		break;
	default:
		break;
	}
}