#include "MainLightHelper.h"

MainLightHelper* MainLightHelper::m_pInstance = NULL;
MainLightHelper* MainLightHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new MainLightHelper;

	return m_pInstance;
}

void MainLightHelper::loop()
{
	MainLightHelper::HandleState();
}

void MainLightHelper::Start()
{
	BaseOnOfDeviceHelper::Start();
	IsFadeWasComplete = false;
}
void MainLightHelper::Stop()
{
	BaseOnOfDeviceHelper::Stop();
	IsFadeWasComplete = false;
}

void MainLightHelper::Toggle()
{
	switch (CurrentLevel)
	{
	case MainLightHelper::Off: CurrentLevel = Low;
		break;
	case MainLightHelper::Low:CurrentLevel = Medium;
		break;
	case MainLightHelper::Medium:CurrentLevel = High;
		break;
	case MainLightHelper::High:CurrentLevel = Off;
		break;
	default:
		break;
	}

	IsFadeWasComplete = false;
	
}

void MainLightHelper::HandleState()
{
	if (!IsFadeWasComplete)
	{
		unsigned long currentMillis = millis();
		if (currentMillis - previousMillis > 50) {
			previousMillis = currentMillis;

			switch (CurrentLevel)
			{
			case MainLightHelper::Off:
			{

				if (currentBright != 0)
				{
					if (currentBright > 0)
					{
						currentBright--;
					}
					else
					{
						currentBright++;
					}
				}
				else
				{
					currentBright = 0;
					IsFadeWasComplete = true;
				}
				break;
			}
			case MainLightHelper::Low:
			case MainLightHelper::Medium:
			case MainLightHelper::High:
			{
				if (currentBright != CurrentLevel)
				{
					if (currentBright > CurrentLevel)
					{
						currentBright--;
					}
					else
					{
						currentBright++;
					}
				}
				else
				{
					currentBright = CurrentLevel;
					IsFadeWasComplete = true;
				}
			}
			break;
			}

			analogWrite(PinNum, currentBright);
		}
	}
}


void MainLightHelper::HandleDayPartChanged(ClockHelper::DayPart dayPart)
{
	switch (dayPart)
	{
	case ClockHelper::Morning:
		CurrentLevel = MainLightHelper::High;
		IsFadeWasComplete = false;
		break;
	case ClockHelper::Day:
		CurrentLevel = MainLightHelper::Medium;
		IsFadeWasComplete = false;
		break;
	case ClockHelper::Evening:
		CurrentLevel = MainLightHelper::Low;
		IsFadeWasComplete = false;
		break;
	case ClockHelper::Night:
		CurrentLevel = MainLightHelper::Off;
		IsFadeWasComplete = false;
		break;
	default:
		break;
	}
}

