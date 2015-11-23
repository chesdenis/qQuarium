#include "qQuariumSetupTimeMode.h"
#include "ClockHelper.h"

void qQuariumSetupTimeMode::loop()
{
	if (!isLcdUpdated)
	{
		LcdLink->clear();
		
		switch (CurrentTimeCategory)
		{
		case MorningOn:
			contextTimeCategory = &(ClockHelper::Instance()->MorningOn);
			break;
		case DayOn:
			contextTimeCategory = &(ClockHelper::Instance()->DayOn);
			break;
		case EveningOn:
			contextTimeCategory = &(ClockHelper::Instance()->EveningOn);
			break;
		case NightOn:
			contextTimeCategory = &(ClockHelper::Instance()->NightOn);
			break;
		default:
			break;
		}

		if (contextTimeCategory != NULL)
		{
			if (contextTimeCategory->TimeName != NULL)
			{
				LcdLink->print(contextTimeCategory->TimeName);
			}

			LcdLink->setCursor(0, 1);
			LcdLink->print(contextTimeCategory->getFormatedTime());

			switch (CurrentMode)
			{
			case qQuariumSetupTimeMode::View:
				LcdLink->noCursor();
				break;
			case qQuariumSetupTimeMode::EditHours:
				LcdLink->setCursor(0, 1);
				LcdLink->cursor();
				break;
			case qQuariumSetupTimeMode::EditMinutes:
				LcdLink->setCursor(3, 1);
				LcdLink->cursor();
				break;
			}
		}

		isLcdUpdated = true;
	}	
}

void qQuariumSetupTimeMode::OkClick()
{
	uint8_t currentMenuIndex = CurrentMode;
	currentMenuIndex++;
	if (currentMenuIndex > modeLastIndex)
	{
		currentMenuIndex = 0;
	}
	CurrentMode = (Mode)currentMenuIndex;

	switch (CurrentMode)
	{
	case qQuariumSetupTimeMode::View:
		contextTimeCategory->isEditMode = false;
		break;
	case qQuariumSetupTimeMode::EditHours:
		contextTimeCategory->isEditMode = true;
		break;
	case qQuariumSetupTimeMode::EditMinutes:
		contextTimeCategory->isEditMode = true;
		break;
	}

	isLcdUpdated = false;
};
void qQuariumSetupTimeMode::CancelClick()
{
	LcdLink->noCursor();
	exit();
};
void qQuariumSetupTimeMode::LeftClick()
{
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentTimeCategory;
		if (currentMenuIndex == 0)
		{
			currentMenuIndex = timeCategoryLastIndex;
		}
		else
		{
			currentMenuIndex--;
		}
		;
		CurrentTimeCategory = (TimeCategory)currentMenuIndex;
	}
	else
	{
		switch (CurrentMode)
		{
		case qQuariumSetupTimeMode::EditHours:
			contextTimeCategory->DecrementHours();
			break;
		case qQuariumSetupTimeMode::EditMinutes:
			contextTimeCategory->DecrementMinutes();
			break;
		}
	}
	
	isLcdUpdated = false;
};

void qQuariumSetupTimeMode::RightClick()
{
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentTimeCategory;
		currentMenuIndex++;
		if (currentMenuIndex > timeCategoryLastIndex)
		{
			currentMenuIndex = 0;
		}
		CurrentTimeCategory = (TimeCategory)currentMenuIndex;
	}
	else
	{
		switch (CurrentMode)
		{
		case qQuariumSetupTimeMode::EditHours:
			contextTimeCategory->IncrementHours();
			break;
		case qQuariumSetupTimeMode::EditMinutes:
			contextTimeCategory->IncrementMinutes();
			break;
		}
	}

	isLcdUpdated = false;
};