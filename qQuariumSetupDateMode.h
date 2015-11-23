#pragma once
#include "qQuariumMode.h"
class qQuariumSetupDateMode:
	public qQuariumMode
{
private:

	int modeLastIndex = 4;
	enum Mode
	{
		View,
		Edit1, // edit first symbol
		Edit2, // edit second symbol
		Edit3, // edit third symbol
		Edit4 // edit fourth symbol
	};

	Mode CurrentMode = View;

	int dateCategoryLastIndex = 5;
	enum DateCategory
	{
		DayOfWeek,
		Day,
		Month,
		Year,
		Hours,
		Minutes
	};

	DateCategory CurrentDateCategory = DayOfWeek;

	char* headerDateCategoryText = NULL;
	
	int8_t currentDayOfWeek = 1;
	int8_t currentDay = 1;
	int8_t currentMonth = 1;
	int16_t currentYear = 1;
	int8_t currentHours = 1;
	int8_t currentMinutes = 1;

	void IncreaseDayOfWeek();
	void IncreaseDay();
	void IncreaseMonth();
	void IncreaseYear();
	void IncreaseHours();
	void IncreaseMinutes();

	void DecreaseDayOfWeek();
	void DecreaseDay();
	void DecreaseMonth();
	void DecreaseYear();
	void DecreaseHours();
	void DecreaseMinutes();

	void SaveTime();

public:
	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
};

