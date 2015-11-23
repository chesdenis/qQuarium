#include "AerationHelper.h"

AerationHelper* AerationHelper::m_pInstance = NULL;
AerationHelper* AerationHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new AerationHelper;

	return m_pInstance;
}

void AerationHelper::HandleDayPartChanged(ClockHelper::DayPart dayPart)
{
	switch (dayPart)
	{
	case ClockHelper::Morning:
	case ClockHelper::Day:
	case ClockHelper::Evening:
	case ClockHelper::Night:
	{
		Start();
	}
	break;
	default:
		break;
	}
}