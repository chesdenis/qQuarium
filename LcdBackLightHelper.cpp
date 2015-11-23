#include "LcdBackLightHelper.h"
#include "ClockHelper.h"
#include "Arduino.h"



LcdBackLightHelper* LcdBackLightHelper::m_pInstance = NULL;
LcdBackLightHelper* LcdBackLightHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new LcdBackLightHelper;

	return m_pInstance;
}

void LcdBackLightHelper::init(uint8_t lcdBackLightPinNum )
{
	LcdBackLightPinNum = lcdBackLightPinNum;
	
}

void LcdBackLightHelper::loop()
{	
	if (!isStateWasUpdated)
	{
		unsigned long currentMillis = millis();

		if (currentMillis - previousMillis > 1000) {
			previousMillis = currentMillis;
			AutoOffCounter++;
		}

		if (AutoOffCounter > 10)
		{
			analogWrite(LcdBackLightPinNum, 0);
			
		    isStateWasUpdated = true;
		}
	}
}

void LcdBackLightHelper::IncreaseLedTime()
{
	AutoOffCounter = 0;
	isStateWasUpdated = false;
	analogWrite(LcdBackLightPinNum, 255);

	unsigned long currentMillis = millis();
	previousMillis = currentMillis;
}
