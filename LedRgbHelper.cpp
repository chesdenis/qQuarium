#include "Arduino.h"
#include "LedRgbHelper.h"
#include "LiquidCrystal.h"
#include "ClockHelper.h"
#include "AquaTemperatureHelper.h"

LedRgbHelper* LedRgbHelper::m_pInstance = NULL;
LedRgbHelper* LedRgbHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new LedRgbHelper;

	return m_pInstance;
}

void LedRgbHelper::loop(ClockHelper::DayPart dayPart)
{
	if (isEditMode) return;

	switch (dayPart)
	{
	case ClockHelper::Morning:
	case ClockHelper::Day:
	case ClockHelper::Evening:
	{
		if (AquaTemperatureHelper::Instance()->isAquaNorm == true)
		{
			if (isAlertSet)
			{
				isAlertSet = false;
			}
		}
		else
		{
			if (!isAlertSet)
			{
				isAlertSet = true;
				if (AquaTemperatureHelper::Instance()->isAquaVeryCold)
				{
					CurrentAlertColor.RedPart = 0;
					CurrentAlertColor.BluePart = 1;
					CurrentAlertColor.GreenPart = 0;

					isAlertSet = true;
				}
				else if (AquaTemperatureHelper::Instance()->isAquaVeryHeat)
				{
					CurrentAlertColor.RedPart = 1;
					CurrentAlertColor.BluePart = 0;
					CurrentAlertColor.GreenPart = 0;

					isAlertSet = true;
				}
			}
		}
	}
	break;
	case ClockHelper::Night:
		if (isAlertSet)
		{
			isAlertSet = false;
		}
		break;
	default:
		break;
	}

	if (!isLedUpdated & isAlertSet == false)
	{
		
		LedRgbHelper::Instance()->ShowDefaultBackLight();
		// we used animation, so led is no updated always.
		isLedUpdated = true;
	}
	if (!isLedUpdated & isAlertSet)
	{
		LedRgbHelper::Instance()->ShowAlertBackLight();
		// we used animation, so led is no updated always.
		isLedUpdated = false;
	}

	
}
int LedRgbHelper::getCurrentBrightness(int brightnessReference)
{
	unsigned long currentMillis = millis();

	double brightness = brightnessReference * cos(2 * PI / 10000 * currentMillis);

	if (brightness > 250)
	{
		return 255;
	}
	else if (brightness < 0)
	{
		// try to read temperature when led backlight was disabled.
		// this is performance issue. Consider to use Arduino Mega?
		AquaTemperatureHelper::Instance()->ReadTemperature();
		return 0;
	}
	else{
		return (int)brightness;
	}
}

void LedRgbHelper::ShowAlertBackLight()
{
	
	CurrentAlertColor.Brightness = getCurrentBrightness(255);

	Show(&CurrentAlertColor);

}

void LedRgbHelper::init(uint8_t redPinNum, uint8_t greenPinNum, uint8_t bluePinNum)
{
	RedPinNum = redPinNum;
	GreenPinNum = greenPinNum;
	BluePinNum = bluePinNum;

	pinMode(redPinNum, OUTPUT);
	pinMode(greenPinNum, OUTPUT);
	pinMode(bluePinNum, OUTPUT);
}

void LedRgbHelper::SetLedOff()
{
	analogWrite(RedPinNum, 0);
	analogWrite(BluePinNum, 0);
	analogWrite(GreenPinNum, 0);
}


void LedRgbHelper::Show(RGBColorHelper colorToShow)
{	
	int sumColorParts = colorToShow.RedPart + colorToShow.GreenPart + colorToShow.BluePart;

	float rK = 0;
	float gK = 0;
	float bK = 0;

	if (sumColorParts != 0)
	{
		float redPartAsFloat = (float)colorToShow.RedPart;
		float greenPartAsFloat = (float)colorToShow.GreenPart;
		float bluePartAsFloat = (float)colorToShow.BluePart;

		float sumColorPartsAsFloat = (float)sumColorParts;

		int brightness = colorToShow.Brightness;
		

		rK = redPartAsFloat / sumColorPartsAsFloat;
		gK = greenPartAsFloat / sumColorPartsAsFloat;
		bK = bluePartAsFloat / sumColorPartsAsFloat;
		
		rK = rK*brightness;
		gK = gK*brightness;
		bK = bK*brightness;
	}
		
	uint8_t totalCParts = (uint8_t)rK + (uint8_t)gK + (uint8_t)bK;
	
	if (totalCParts <= 255){
		analogWrite(RedPinNum, (uint8_t)rK);
		analogWrite(GreenPinNum, (uint8_t)gK);
		analogWrite(BluePinNum, (uint8_t)bK);
	}	
}

void LedRgbHelper::Show(RGBColorHelper* colorToShow)
{
	RGBColorHelper colorValue = *colorToShow;

	Show(colorValue);
}

void LedRgbHelper::ShowDefaultBackLight()
{
	ClockHelper::DayPart dayPart = ClockHelper::Instance()->GetDayPart();
	switch (dayPart)
	{
	case ClockHelper::Morning:
		Show(&MorningLedBackLight);
		break;
	case ClockHelper::Day:
		Show(&DayLedBackLight);
		break;
	case ClockHelper::Evening:
		Show(&EveningLedBackLight);
		break;
	case ClockHelper::Night:
		Show(&NightLedBackLight);
		break;
	}

};

void LedRgbHelper::HandleDayPartChanged(ClockHelper::DayPart dayPart)
{
	isLedUpdated = false;
};