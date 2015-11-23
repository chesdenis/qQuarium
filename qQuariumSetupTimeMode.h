#pragma once
#include "qQuariumMode.h"
#include "TimeHelper.h"
class qQuariumSetupTimeMode :
	public qQuariumMode
{
private:

	int modeLastIndex = 2;
	enum Mode
	{
		View,
		EditHours,
		EditMinutes
	};

	Mode CurrentMode = View;

	int timeCategoryLastIndex = 3;
	enum TimeCategory
	{ 
		MorningOn,
		DayOn,
		EveningOn,
		NightOn
	};

	TimeCategory CurrentTimeCategory = MorningOn;

	TimeHelper* contextTimeCategory = NULL;
	char* headerTimeCategoryText = NULL;
	
public:
	
	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
};

