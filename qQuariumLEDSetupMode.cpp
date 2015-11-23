#include "qQuariumLEDSetupMode.h"
#include "LedRgbHelper.h"

void qQuariumLEDSetupMode::loop()
{
	if (!isLcdUpdated)
	{
		LedRgbHelper::Instance()->isEditMode = true;

		
		LcdLink->clear();

		switch (CurrentLedCategory)
		{
		case Morning:
			contextLedCategory = &(LedRgbHelper::Instance()->MorningLedBackLight);
			break;
		case Day:
			contextLedCategory = &(LedRgbHelper::Instance()->DayLedBackLight);
			break;
		case Evening:
			contextLedCategory = &(LedRgbHelper::Instance()->EveningLedBackLight);
			break;
		case Night:
			contextLedCategory = &(LedRgbHelper::Instance()->NightLedBackLight);
			break;
		}
		
		if (contextLedCategory != NULL)
		{
			if (contextLedCategory->Title != NULL)
			{
				LcdLink->print(contextLedCategory->Title);
			}

			LcdLink->setCursor(0, 1);

			LcdLink->print(contextLedCategory->
				GetPrintComponentValue(&(contextLedCategory->RedPart)));

			LcdLink->print(":");
			LcdLink->print(contextLedCategory->
				GetPrintComponentValue(&(contextLedCategory->GreenPart)));

			LcdLink->print(":");
			LcdLink->print(contextLedCategory->
				GetPrintComponentValue(&(contextLedCategory->BluePart)));

			LcdLink->print(",");
			LcdLink->print(contextLedCategory->
				GetPrintComponentValue(&(contextLedCategory->Brightness)));

			switch (CurrentMode)
			{
			case View:
				LcdLink->noCursor();
				break;
			case EditRed:
				LcdLink->setCursor(0, 1);
				LcdLink->cursor();
				break;
			case EditGreen:
				LcdLink->setCursor(4, 1);
				LcdLink->cursor();
				break;
			case EditBlue:
				LcdLink->setCursor(8, 1);
				LcdLink->cursor();
				break;
			case EditBrightness:
				LcdLink->setCursor(12, 1);
				LcdLink->cursor();
				break;
			}

		}

	    LedRgbHelper::Instance()->Show(contextLedCategory);
		

		isLcdUpdated = true;
	}
};

void qQuariumLEDSetupMode::OkClick()
{
	uint8_t currentMenuIndex = CurrentMode;
	currentMenuIndex++;
	if (currentMenuIndex > modeLastIndex)
	{
		currentMenuIndex = 0;
	}
	CurrentMode = (Mode)currentMenuIndex;

	isLcdUpdated = false;
};

void qQuariumLEDSetupMode::CancelClick()
{
	LcdLink->noCursor();

	LedRgbHelper::Instance()->isEditMode = false;
	LedRgbHelper::Instance()->SetLedOff();
	LedRgbHelper::Instance()->isLedUpdated = false;
	exit();
};

void qQuariumLEDSetupMode::LeftClick()
{
	
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentLedCategory;
		if (currentMenuIndex == 0)
		{
			currentMenuIndex = ledCategoryLastIndex;
		}
		else
		{
			currentMenuIndex--;
		}
		CurrentLedCategory = (LedCategory)currentMenuIndex;
	}
	else
	{
		if (contextLedCategory != NULL)
		{
			switch (CurrentMode)
			{
			case EditRed:
				contextLedCategory->Decrement(&(contextLedCategory->RedPart));
				break;
			case EditGreen:
				contextLedCategory->Decrement(&(contextLedCategory->GreenPart));
				break;
			case EditBlue:
				contextLedCategory->Decrement(&(contextLedCategory->BluePart));
				break;
			case EditBrightness:
				contextLedCategory->DecrementBright();
				break;
			}
		}
		
	}

	isLcdUpdated = false;
};

void qQuariumLEDSetupMode::RightClick()
{
	if (CurrentMode == View)
	{
		uint8_t currentMenuIndex = CurrentLedCategory;
		currentMenuIndex++;
		if (currentMenuIndex > ledCategoryLastIndex)
		{
			currentMenuIndex = 0;
		}
		CurrentLedCategory = (LedCategory)currentMenuIndex;
	}
	
	else
	{
		if (contextLedCategory != NULL)
		{
			switch (CurrentMode)
			{
			case EditRed:
				contextLedCategory->Increment(&(contextLedCategory->RedPart));
				break;
			case EditGreen:
				contextLedCategory->Increment(&(contextLedCategory->GreenPart));
				break;
			case EditBlue:
				contextLedCategory->Increment(&(contextLedCategory->BluePart));
				break;
			case EditBrightness:
				contextLedCategory->IncrementBright();
				break;
			}
		}
	}

	isLcdUpdated = false;
};