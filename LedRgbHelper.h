#include "Arduino.h"
#include "LiquidCrystal.h"    // include the library
#include "RGBColorHelper.h"
#include "TimeHelper.h"
#include "ClockHelper.h"

class LedRgbHelper
{
private:
	LedRgbHelper(){};
	LedRgbHelper(LedRgbHelper const&){};
	LedRgbHelper& operator=(LedRgbHelper const&){};
	static LedRgbHelper* m_pInstance;

	uint8_t RedPinNum;
	uint8_t GreenPinNum;
	uint8_t BluePinNum;

	int getCurrentBrightness(int brightnessReference);
public:

	void init(uint8_t redPinNum, uint8_t greenPinNum, uint8_t bluePinNum);

	void SetLedOff();

	bool isLedUpdated = false;
	bool isEditMode = false;


	static LedRgbHelper* Instance();

	// Стандартные цвета
	RGBColorHelper Red = RGBColorHelper(255, 0, 0, 10);
	RGBColorHelper Green = RGBColorHelper(0, 255, 0, 20);
	RGBColorHelper Blue = RGBColorHelper(0, 0, 255, 30);

	RGBColorHelper MorningLedBackLight = RGBColorHelper("Morn(R:G:B,W)");
	RGBColorHelper DayLedBackLight = RGBColorHelper("Day(R:G:B,W)");
	RGBColorHelper EveningLedBackLight = RGBColorHelper("Even(R:G:B,W)");
	RGBColorHelper NightLedBackLight = RGBColorHelper("Night(R:G:B,W)");

	
	RGBColorHelper GetColorByIndex();

	RGBColorHelper CurrentAlertColor = RGBColorHelper("Alert");
	bool isAlertSet = false;
	
	
	void Show(RGBColorHelper colorToShow);
	void Show(RGBColorHelper* colorToShow);


	void ShowDefaultBackLight();
	void ShowAlertBackLight();

	void loop(ClockHelper::DayPart dayPart);
	void HandleDayPartChanged(ClockHelper::DayPart dayPart);
	
};