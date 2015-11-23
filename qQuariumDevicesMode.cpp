#include "qQuariumDevicesMode.h"
#include "MainLightHelper.h"
#include "AerationHelper.h"
#include "CompressorHelper.h"
#include "LcdBackLightHelper.h"
#include "VulcanusHelper.h"
#include "PumpHelper.h"

void qQuariumDevicesMode::loop()
{
	if (!isLcdUpdated)
	{
		LcdLink->clear();

		switch (CurrentDeviceCategory)
		{
		
		case MainLight:
			LcdLink->print("Main light");
			break;
		case Aeration:
			LcdLink->print("Aeration");
			break;
		case Compressor:
			LcdLink->print("Compressor");
			break;
		case Vulcanius:
			LcdLink->print("Vulcanius");
			break;
		case Pump:
			LcdLink->print("Pump");
			break;
		default:
			break;
		}
		
		LcdLink->setCursor(0, 1);

		BaseOnOfDeviceHelper* deviceHelper = GetDeviceHelper();
		if (deviceHelper != NULL)
		{
			switch (CurrentDeviceCategory)
			{
			case qQuariumDevicesMode::MainLight:
			{
				MainLightHelper* mainLightHelper = (MainLightHelper*)deviceHelper;

				switch (mainLightHelper->CurrentLevel)
				{
				case MainLightHelper::Off:LcdLink->print("Off");
					break;
				case MainLightHelper::Low:LcdLink->print("Low");
					break;
				case MainLightHelper::Medium:LcdLink->print("Medium");
					break;
				case MainLightHelper::High:LcdLink->print("High");
					break;
				default:
					break;
				}
			}
				break;
			default:
				if (deviceHelper->IsActive)
				{
					LcdLink->print("Is On");
				}
				else
				{
					LcdLink->print("Is Off");
				}
				break;
			}
		}

		isLcdUpdated = true;
	}
}

void qQuariumDevicesMode::OkClick()
{
	switch (CurrentDeviceCategory)
	{
	case qQuariumDevicesMode::MainLight:MainLightHelper::Instance()->Toggle();
		break;
	case qQuariumDevicesMode::Aeration:AerationHelper::Instance()->Toggle();
		break;
	case qQuariumDevicesMode::Compressor:CompressorHelper::Instance()->Toggle();
		break;
	case qQuariumDevicesMode::Vulcanius:VulcanusHelper::Instance()->Toggle();
		break;
	case qQuariumDevicesMode::Pump:PumpHelper::Instance()->Toggle();
		break;
	default:
		break;
	}

	isLcdUpdated = false;
}

void qQuariumDevicesMode::CancelClick()
{
	exit();
}

void qQuariumDevicesMode::LeftClick()
{
	uint8_t currentMenuIndex = CurrentDeviceCategory;
	if (currentMenuIndex == 0)
	{
		currentMenuIndex = deviceCategoryLastIndex;
	}
	else
	{
		currentMenuIndex--;
	}

	CurrentDeviceCategory = (DeviceCategory)currentMenuIndex;
	
	isLcdUpdated = false;
}

void qQuariumDevicesMode::RightClick()
{
	uint8_t currentMenuIndex = CurrentDeviceCategory;
	currentMenuIndex++;
	if (currentMenuIndex > deviceCategoryLastIndex)
	{
		currentMenuIndex = 0;
	}

	CurrentDeviceCategory = (DeviceCategory)currentMenuIndex;

	isLcdUpdated = false;
}

BaseOnOfDeviceHelper* qQuariumDevicesMode::GetDeviceHelper()
{
	switch (CurrentDeviceCategory)
	{
	case qQuariumDevicesMode::MainLight: return MainLightHelper::Instance();
	case Aeration: return AerationHelper::Instance();
	case Compressor:return CompressorHelper::Instance();
	case Vulcanius:return VulcanusHelper::Instance();
	case Pump: return PumpHelper::Instance();
	default:
		return NULL;
	}
}