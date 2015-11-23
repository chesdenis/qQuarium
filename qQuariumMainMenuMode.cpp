#include "qQuariumMainMenuMode.h"
#include "ClockHelper.h"
#include "AquaTemperatureHelper.h"

void qQuariumMainMenuMode::loop()
{
	
	if (currentMenuItemId == 0)
	{
		isUpdateByTimerEnabled = true;

		if (!isLcdUpdated | !ClockHelper::Instance()->isUpdatedByTimer)
		{
			ClockHelper::Instance()->Clock.getTime();
			
			LcdLink->clear();

			LcdLink->print(ClockHelper::Instance()->GetCurrentTimeFormatedDay());
			LcdLink->print(" ");
			LcdLink->print(ClockHelper::Instance()->GetCurrentTimeFormatedDate());
						
			LcdLink->setCursor(0, 1);
			LcdLink->print(ClockHelper::Instance()->GetCurrentTimeFormatedTime());
			LcdLink->print(" \x1F");
			LcdLink->print(AquaTemperatureHelper::Instance()->GetTemperatureText());
			LcdLink->print("\x99""C");


			isLcdUpdated = true;
		}
	}
	else
	{
		isUpdateByTimerEnabled = false;

		if (!isLcdUpdated)
		{
			LcdLink->clear();
			LcdLink->print(getMenuItemTextById(currentMenuItemId));
			isLcdUpdated = true;
		}
	}
	
}

void qQuariumMainMenuMode::OkClick()
{
	
	if (isCurrentModeLinkLinkDefined)
	{
		switch (currentMenuItemId)
		{
		case qQuariumMainMenuMode::Info:
			break;
		case qQuariumMainMenuMode::SetupTime:
			if (setupTimeModeLink != NULL)
			{
				*CurrentModeLinkLink = setupTimeModeLink;
			}
			break;
		case qQuariumMainMenuMode::SetupDate:
			if (setupDateModeLink != NULL)
			{
				*CurrentModeLinkLink = setupDateModeLink;
			}
			break;
		case qQuariumMainMenuMode::Temperature:
			if (temperatureModeLink != NULL)
			{
				*CurrentModeLinkLink = temperatureModeLink;
			}
			break;
		case qQuariumMainMenuMode::Climate:
			if (climateModeLink != NULL)
			{
				*CurrentModeLinkLink = climateModeLink;
			}
			break;
			
		case qQuariumMainMenuMode::BackLight:
			if (ledSetupModeLink != NULL)
			{
				*CurrentModeLinkLink = ledSetupModeLink;
			}
			break;
		case qQuariumMainMenuMode::Devices:
			if (devicesModeLink != NULL)
			{
				*CurrentModeLinkLink = devicesModeLink;
			}
			break;
		default:
			break;
		}

	}

};
void qQuariumMainMenuMode::CancelClick()
{
	currentMenuItemId = 0;
	isLcdUpdated = false;
};

void qQuariumMainMenuMode::LeftClick()
{
	currentMenuItemId--;
	if (currentMenuItemId < 0)
	{
		currentMenuItemId = lastMenuIndex;
	}
	isLcdUpdated = false;
};

void qQuariumMainMenuMode::RightClick()
{
	currentMenuItemId++;
	if (currentMenuItemId > lastMenuIndex)
	{
		currentMenuItemId = 0;
	}
	isLcdUpdated = false;
};

char* qQuariumMainMenuMode::getMenuItemTextById(int menuItemId)
{
	switch (menuItemId)
	{
	case Info: { return ""; };
	case SetupTime:{return "Day parts..."; };
	case SetupDate:{return "Setup date..."; };
	case Temperature:{ return "Temperature..."; };
	case Climate:{return "Climate..."; };
	case BackLight:{ return "Led back light..."; };
	case Devices: {return "Devices"; };
	default:
		return "";
	}
}