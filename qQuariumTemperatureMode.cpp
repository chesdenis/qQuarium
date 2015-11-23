#include "qQuariumTemperatureMode.h"
#include "ClockHelper.h"
#include "AquaTemperatureHelper.h"


void qQuariumTemperatureMode::loop()
{
	if (!isLcdUpdated | !ClockHelper::Instance()->isUpdatedByTimer)
	{
		LcdLink->clear();

		switch (CurrentTemperatureCategory)
		{
		case CurrentTemperature:
			LcdLink->print("Water:");
			LcdLink->setCursor(0, 1);
			LcdLink->print("\x1F");
			LcdLink->print(AquaTemperatureHelper::Instance()->GetTemperatureText());
			LcdLink->print("\x99""C");
			break;
		case MinTemperature:
			LcdLink->print("Min:");
			LcdLink->setCursor(0, 1);
			LcdLink->print("\x1F");
			LcdLink->print(AquaTemperatureHelper::Instance()->minAquaTemp);
			LcdLink->print("\x99""C");
			break;
		case MaxTemperature:
			LcdLink->print("Max:");
			LcdLink->setCursor(0, 1);
			LcdLink->print("\x1F");
			LcdLink->print(AquaTemperatureHelper::Instance()->maxAquaTemp);
			LcdLink->print("\x99""C");
			break;
		}

		LcdLink->setCursor(0, 1);
		switch (CurrentMode)
		{
		case qQuariumTemperatureMode::View:
			LcdLink->noCursor();
			break;
		case qQuariumTemperatureMode::Edit:
			LcdLink->setCursor(0, 1);
			LcdLink->cursor();
			break;
		}
		
		isLcdUpdated = true;
	}
};

void qQuariumTemperatureMode::OkClick()
{
	if (CurrentTemperatureCategory != CurrentTemperature)
	{
		uint8_t currentMenuIndex = CurrentMode;
		currentMenuIndex++;
		if (currentMenuIndex > modeLastIndex)
		{
			currentMenuIndex = 0;
		}
		CurrentMode = (Mode)currentMenuIndex;
	}
	
	isLcdUpdated = false;
}; 

void qQuariumTemperatureMode::CancelClick()
{
	LcdLink->noCursor();
	exit();
};

void qQuariumTemperatureMode::LeftClick()
{
	if (CurrentMode != View &&
		CurrentTemperatureCategory != CurrentTemperature)
	{
		switch (CurrentTemperatureCategory)
		{
		case qQuariumTemperatureMode::MinTemperature:
			AquaTemperatureHelper::Instance()->DecreaseMinTemp();
			break;
		case qQuariumTemperatureMode::MaxTemperature:
			AquaTemperatureHelper::Instance()->DecreaseMaxTemp();
			break;
		}
	}
	else
	{
		uint8_t currentMenuIndex = CurrentTemperatureCategory;
		if (currentMenuIndex == 0)
		{
			currentMenuIndex = temperatureCategoryLastIndex;
		}
		else
		{
			currentMenuIndex--;
		}
		
		CurrentTemperatureCategory = 
			(TemperatureCategory)currentMenuIndex;

	}

	isLcdUpdated = false;
};

void qQuariumTemperatureMode::RightClick()
{
	if (CurrentMode != View )
	{
		switch (CurrentTemperatureCategory)
		{
		case qQuariumTemperatureMode::MinTemperature:    
			AquaTemperatureHelper::Instance()->IncreaseMinTemp();
			break;
		case qQuariumTemperatureMode::MaxTemperature:
			AquaTemperatureHelper::Instance()->IncreaseMaxTemp();
			break;
		}
	}
	else
	{
		uint8_t currentMenuIndex = CurrentTemperatureCategory;
		currentMenuIndex++;
		if (currentMenuIndex > temperatureCategoryLastIndex)
		{
			currentMenuIndex = 0;
		}

		CurrentTemperatureCategory =
			(TemperatureCategory)currentMenuIndex;

	}

	isLcdUpdated = false;
};