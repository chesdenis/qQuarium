#include "qQuariumSetupDateMode.h"
#include "ClockHelper.h"

void qQuariumSetupDateMode::loop()
{
	if (!isLcdUpdated)
	{
		LcdLink->clear();

		if (CurrentMode == View)
		{
			ClockHelper::Instance()->Clock.getTime();
			currentDayOfWeek = ClockHelper::Instance()->Clock.dayOfWeek;
			currentDay = ClockHelper::Instance()->Clock.dayOfMonth;
			currentMonth = ClockHelper::Instance()->Clock.month;
			currentYear = ClockHelper::Instance()->Clock.year + 2000;

			currentHours = ClockHelper::Instance()->Clock.hour;
			currentMinutes = ClockHelper::Instance()->Clock.minute;

			
		}
		

		switch (CurrentDateCategory)
		{
		case DayOfWeek:
			LcdLink->print("Day of week:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetFormatedDayLong(currentDayOfWeek));
			break;
		case Day:
			LcdLink->print("Current day:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetIntValAsTwoChars(currentDay));
			break;
		case Month:
			LcdLink->print("Current month:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetIntValAsTwoChars(currentMonth));
			break;
		case Year:
			LcdLink->print("Current year:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetYearNum(currentYear));
			break;
		case Hours:
			LcdLink->print("Current hour:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetIntValAsTwoChars(currentHours));
			break;
		case Minutes:
			LcdLink->print("Current minute:");
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetIntValAsTwoChars(currentMinutes));
			break;
		default:
			break;
		}

		LcdLink->setCursor(0, 1);
		switch (CurrentMode)
		{
		case qQuariumSetupDateMode::View:
			LcdLink->noCursor();
			break;
		case qQuariumSetupDateMode::Edit1:
			LcdLink->setCursor(0, 1);
			LcdLink->cursor();
			break;
		case qQuariumSetupDateMode::Edit2:
			LcdLink->setCursor(1, 1);
			LcdLink->cursor();
			break;
		case qQuariumSetupDateMode::Edit3:
		    LcdLink->setCursor(2, 1);
			LcdLink->cursor();
			break;
		case qQuariumSetupDateMode::Edit4:
			LcdLink->setCursor(3, 1);
			LcdLink->cursor();
			break;
		default:
			break;
		}
		

		isLcdUpdated = true;

	}
}

void qQuariumSetupDateMode::OkClick()
{
	uint8_t currentMenuIndex = CurrentMode;
	currentMenuIndex++;

	switch (CurrentDateCategory)
	{
	case qQuariumSetupDateMode::DayOfWeek:
		if (currentMenuIndex > modeLastIndex - 3)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	case qQuariumSetupDateMode::Day:
		if (currentMenuIndex > modeLastIndex - 2)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	case qQuariumSetupDateMode::Month:
		if (currentMenuIndex > modeLastIndex-2)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	case qQuariumSetupDateMode::Year:
		if (currentMenuIndex > modeLastIndex)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	case qQuariumSetupDateMode::Hours:
		if (currentMenuIndex > modeLastIndex - 2)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	case qQuariumSetupDateMode::Minutes:
		if (currentMenuIndex > modeLastIndex - 2)
		{
			currentMenuIndex = 0;
			SaveTime();
		}
		break;
	default:
		break;
	}

	
	CurrentMode = (Mode)currentMenuIndex;

	isLcdUpdated = false;
}

void qQuariumSetupDateMode::SaveTime()
{
	ClockHelper::Instance()->Clock.fillByHMS(currentHours, currentMinutes, 0);
	ClockHelper::Instance()->Clock.fillByYMD(currentYear, currentMonth, currentDay);
	ClockHelper::Instance()->Clock.fillDayOfWeek(currentDayOfWeek);

	ClockHelper::Instance()->Clock.setTime();
}

void qQuariumSetupDateMode::CancelClick()
{
	CurrentMode = View;
	SaveTime();
	LcdLink->noCursor();
	exit();
}

void qQuariumSetupDateMode::LeftClick()
{
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentDateCategory;
		if (currentMenuIndex == 0)
		{
			currentMenuIndex = dateCategoryLastIndex;
		}
		else
		{
			currentMenuIndex--;
		}
		;
		CurrentDateCategory = (DateCategory)currentMenuIndex;
	}
	else
	{
		switch (CurrentDateCategory)
		{
		case qQuariumSetupDateMode::DayOfWeek: DecreaseDayOfWeek();
			break;
		case qQuariumSetupDateMode::Day: DecreaseDay();
			break;
		case qQuariumSetupDateMode::Month: DecreaseMonth();
			break;
		case qQuariumSetupDateMode::Year: DecreaseYear();
			break;

		case qQuariumSetupDateMode::Hours: DecreaseHours();
			break;
		case qQuariumSetupDateMode::Minutes: DecreaseMinutes();
			break;

		default:
			break;
		}
	}

	isLcdUpdated = false;
}

void qQuariumSetupDateMode::RightClick()
{
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentDateCategory;
		currentMenuIndex++;
		if (currentMenuIndex > dateCategoryLastIndex)
		{
			currentMenuIndex = 0;
		}
		CurrentDateCategory = (DateCategory)currentMenuIndex;
	}
	else
	{
		switch (CurrentDateCategory)
		{
		case qQuariumSetupDateMode::DayOfWeek: IncreaseDayOfWeek();
			break;
		case qQuariumSetupDateMode::Day: IncreaseDay();
			break;
		case qQuariumSetupDateMode::Month: IncreaseMonth();
			break;
		case qQuariumSetupDateMode::Year: IncreaseYear();
			break;

		case qQuariumSetupDateMode::Hours: IncreaseHours();
			break;
		case qQuariumSetupDateMode::Minutes: IncreaseMinutes();
			break;

		default:
			break;
		}

	}
	isLcdUpdated = false;
}

void qQuariumSetupDateMode::IncreaseDayOfWeek()
{
	currentDayOfWeek++;

	if (currentDayOfWeek > 7)
		currentDayOfWeek = 7;
};
void qQuariumSetupDateMode::IncreaseDay()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentDay = currentDay + 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentDay = currentDay + 1;
		break;
	default:
		break;
	}

	if (currentDay > 31)
		currentDay = 31;
};
void qQuariumSetupDateMode::IncreaseMonth()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentMonth = currentMonth + 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentMonth = currentMonth + 1;
		break;
	default:
		break;
	}

	if (currentMonth > 12)
		currentMonth = 12;
};
void qQuariumSetupDateMode::IncreaseYear()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentYear = currentYear + 1000;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentYear = currentYear + 100;
		break;
	case qQuariumSetupDateMode::Edit3:
		currentYear = currentYear + 10;
		break;
	case qQuariumSetupDateMode::Edit4:
		currentYear = currentYear + 1;
		break;
	default:
		break;
	}

	if (currentYear > 2200)
		currentYear = 2000;
};

void qQuariumSetupDateMode::IncreaseHours()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentHours = currentHours + 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentHours = currentHours + 1;
		break;
	default:
		break;
	}

	if (currentHours > 23)
		currentHours = 0;
};

void qQuariumSetupDateMode::IncreaseMinutes()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentMinutes = currentMinutes + 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentMinutes = currentMinutes + 1;
		break;
	default:
		break;
	}

	if (currentMinutes > 59)
		currentMinutes = 0;
};

void qQuariumSetupDateMode::DecreaseDayOfWeek()
{
	currentDayOfWeek--;

	if (currentDayOfWeek < 1)
		currentDayOfWeek = 1;
};
void qQuariumSetupDateMode::DecreaseDay()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentDay = currentDay - 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentDay = currentDay - 1;
		break;
	default:
		break;
	}
	
	if (currentDay < 1)
		currentDay = 1;
};
void qQuariumSetupDateMode::DecreaseMonth()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentMonth = currentMonth - 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentMonth = currentMonth - 1;
		break;
	default:
		break;
	}

	if (currentMonth < 1)
		currentMonth = 1;
};
void qQuariumSetupDateMode::DecreaseYear()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentYear = currentYear - 1000;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentYear = currentYear - 100;
		break;
	case qQuariumSetupDateMode::Edit3:
		currentYear = currentYear - 10;
		break;
	case qQuariumSetupDateMode::Edit4:
		currentYear = currentYear - 1;
		break;
	default:
		break;
	}

	if (currentYear < 2000)
		currentYear = 2000;
};

void qQuariumSetupDateMode::DecreaseHours()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentHours = currentHours - 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentHours = currentHours - 1;
		break;
	default:
		break;
	}

	if (currentHours < 0)
		currentHours = 0;
};

void qQuariumSetupDateMode::DecreaseMinutes()
{
	switch (CurrentMode)
	{
	case qQuariumSetupDateMode::Edit1:
		currentMinutes = currentMinutes - 10;
		break;
	case qQuariumSetupDateMode::Edit2:
		currentMinutes = currentMinutes - 1;
		break;
	default:
		break;
	}

	if (currentMinutes < 0)
		currentMinutes = 0;
};