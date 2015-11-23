#pragma once
#include "qQuariumMode.h"
#include "RGBColorHelper.h"
#include "TimeHelper.h"

class qQuariumLEDSetupMode :
	public qQuariumMode
{
private:

	int ledCategoryLastIndex = 3;
	enum LedCategory 
	{
		Morning,
		Day,
		Evening,
		Night
	};

	LedCategory CurrentLedCategory = Morning;

	int modeLastIndex = 4;
	enum Mode
	{
		View,
		EditRed,
		EditGreen,
		EditBlue,
		EditBrightness
	};

	Mode CurrentMode = View;

	RGBColorHelper* contextLedCategory = NULL;
	char* headerLedCategoryText = NULL;
	
public:
	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
	
};

