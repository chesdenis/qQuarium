#pragma once
#include "qQuariumMode.h"
class qQuariumTemperatureMode :
	public qQuariumMode
{
private:
	
	int modeLastIndex = 1;
	enum Mode
	{
		View,
		Edit
	};

	Mode CurrentMode = View;

	int temperatureCategoryLastIndex = 2;
	enum TemperatureCategory
	{
		CurrentTemperature,
		MinTemperature,
		MaxTemperature
	};

	TemperatureCategory CurrentTemperatureCategory = CurrentTemperature;
	
	char* headerTemperatureCategoryText = NULL;


public:
	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
};

