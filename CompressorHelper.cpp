#include "CompressorHelper.h"

CompressorHelper* CompressorHelper::m_pInstance = NULL;
CompressorHelper* CompressorHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new CompressorHelper;

	return m_pInstance;
}

void CompressorHelper::HandleDayPartChanged(ClockHelper::DayPart dayPart)
{
	switch (dayPart)
	{
	case ClockHelper::Evening:
	{
		Start();
	}
	break;
	default:
	{
		Stop();
	}
	break;
	}
}