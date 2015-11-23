#include "LedRgbHelper.h"
#include "LiquidCrystal.h" 
#include "ButtonHandler.h"
#include "qQuariumMode.h"
#include "qQuariumMainMenuMode.h"
#include "qQuariumSetupTimeMode.h"
#include "qQuariumSetupDateMode.h"
#include "qQuariumDevicesMode.h"
#include "qQuariumRoomClimateMode.h"
#include "qQuariumTemperatureMode.h"

#include "ClockHelper.h"
#include "AquaTemperatureHelper.h"
#include "RoomTemperature.h"
#include "Wire.h"
#include "OneWire.h"
#include "DS1307.h"
#include "dht11.h"
#include "MainLightHelper.h"
#include "CompressorHelper.h"
#include "AerationHelper.h"
#include "IRremote.h"
#include "BeepHelper.h"
#include "LcdBackLightHelper.h"
#include "VulcanusHelper.h"
#include "PumpHelper.h"

LiquidCrystal Lcd(53, 51, 49, 47, 45, 43);     

ButtonHandler BtnLeftHandler(ButtonHandler::Left);
ButtonHandler BtnOkHandler(ButtonHandler::Ok);
ButtonHandler BtnCancelHandler(ButtonHandler::Cancel);
ButtonHandler BtnRightHandler(ButtonHandler::Right);

qQuariumMode* Mode; // Link to active mode

qQuariumMainMenuMode MainMenuMode;
qQuariumSetupTimeMode SetupTimeMode;
qQuariumTemperatureMode TemperatureMode;
qQuariumLEDSetupMode LedSetupMode;
qQuariumSetupDateMode SetupDateMode;
qQuariumRoomClimateMode RoomClimateMode;
qQuariumDevicesMode DevicesMode;



IRrecv irrecv(2);
decode_results irResults;
ClockHelper::DayPart currentDayPart = ClockHelper::Morning;



void setup()
{
	Serial.begin(9600);

	setup_full();
}



void loop()
{

	loop_full();

}

#pragma region FullControl


void setup_full()
{
	// Запускаем библиотеку IRRemote
	irrecv.enableIRIn();

	ClockHelper::Instance()->Clock.begin();

	Lcd.begin(16, 2);
	Lcd.clear();
	
	AquaTemperatureHelper::Instance()->setup(31);
	RoomTemperature::Instance()->setup(A1);


	BeepHelper::Instance()->setup(22);

	LedRgbHelper::Instance()->init(13, 12, 4);

	MainLightHelper::Instance()->Init(5);

	AerationHelper::Instance()->Init(33);

	VulcanusHelper::Instance()->Init(8);

	CompressorHelper::Instance()->Init(35);

	PumpHelper::Instance()->Init(39);

	MainMenuMode.init(&Lcd, &Mode);

	SetupTimeMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.setupTimeModeLink = &SetupTimeMode;

	SetupDateMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.setupDateModeLink = &SetupDateMode;

	TemperatureMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.temperatureModeLink = &TemperatureMode;

	RoomClimateMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.climateModeLink = &RoomClimateMode;

	LedSetupMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.ledSetupModeLink = &LedSetupMode;

	DevicesMode.init(&Lcd, &MainMenuMode, &Mode);
	MainMenuMode.devicesModeLink = &DevicesMode;

	Mode = &MainMenuMode;

	BtnOkHandler.Init(&Mode);
	BtnCancelHandler.Init(&Mode);
	BtnLeftHandler.Init(&Mode);
	BtnRightHandler.Init(&Mode);

	LcdBackLightHelper::Instance()->init(24);
	LcdBackLightHelper::Instance()->IncreaseLedTime();

	ClockHelper::Instance()->MorningOn.Hours = 9;
	ClockHelper::Instance()->MorningOn.Minutes = 00;

	ClockHelper::Instance()->DayOn.Hours = 12;
	ClockHelper::Instance()->DayOn.Minutes = 00;

	ClockHelper::Instance()->EveningOn.Hours = 18;
	ClockHelper::Instance()->EveningOn.Minutes = 00;

	ClockHelper::Instance()->NightOn.Hours = 23;
	ClockHelper::Instance()->NightOn.Minutes = 00;

	LedRgbHelper::Instance()->MorningLedBackLight.RedPart = 0;
	LedRgbHelper::Instance()->MorningLedBackLight.GreenPart = 1;
	LedRgbHelper::Instance()->MorningLedBackLight.BluePart = 0;
	LedRgbHelper::Instance()->MorningLedBackLight.Brightness = 10;

	LedRgbHelper::Instance()->DayLedBackLight.RedPart = 1;
	LedRgbHelper::Instance()->DayLedBackLight.GreenPart = 1;
	LedRgbHelper::Instance()->DayLedBackLight.BluePart = 0;
	LedRgbHelper::Instance()->DayLedBackLight.Brightness = 10;

	LedRgbHelper::Instance()->EveningLedBackLight.RedPart = 1;
	LedRgbHelper::Instance()->EveningLedBackLight.GreenPart = 0;
	LedRgbHelper::Instance()->EveningLedBackLight.BluePart = 1;
	LedRgbHelper::Instance()->EveningLedBackLight.Brightness = 10;

	LedRgbHelper::Instance()->NightLedBackLight.RedPart = 0;
	LedRgbHelper::Instance()->NightLedBackLight.GreenPart = 0;
	LedRgbHelper::Instance()->NightLedBackLight.BluePart = 0;
	LedRgbHelper::Instance()->NightLedBackLight.Brightness = 0;

	// Сообщаем пользователю, что мы запустились тройным пиком
	BeepHelper::Instance()->beep(500, 100); delay(100);
	BeepHelper::Instance()->beep(500, 100); delay(100);
	BeepHelper::Instance()->beep(500, 100); delay(100);

	// Запускаем процедуру "обучения"
	learn();

	// Пищим в знак окончания процедуры обучения
	BeepHelper::Instance()->beep(500, 1000);
}

void loop_full(){



	ClockHelper::Instance()->loop();
	AquaTemperatureHelper::Instance()->loop();
	RoomTemperature::Instance()->loop();

	Mode->loop();

	if (irrecv.decode(&irResults)) {
		BtnOkHandler.Handle(&irResults);
		BtnCancelHandler.Handle(&irResults);
		BtnLeftHandler.Handle(&irResults);
		BtnRightHandler.Handle(&irResults);

		irrecv.resume();
	}

	ClockHelper::DayPart dayPart = ClockHelper::Instance()->GetDayPart();
	if (dayPart != currentDayPart)
	{
		currentDayPart = dayPart;
		MainLightHelper::Instance()->HandleDayPartChanged(dayPart);
		LedRgbHelper::Instance()->HandleDayPartChanged(dayPart);
		AerationHelper::Instance()->HandleDayPartChanged(dayPart);
		CompressorHelper::Instance()->HandleDayPartChanged(dayPart);
		VulcanusHelper::Instance()->HandleDayPartChanged(dayPart);
	}
	

	
	LcdBackLightHelper::Instance()->loop();
	VulcanusHelper::Instance()->loop();
	MainLightHelper::Instance()->loop();

	if (ClockHelper::Instance()->isUpdatedByTimer == false)
	{
		LedRgbHelper::Instance()->isLedUpdated = false;
		ClockHelper::Instance()->isUpdatedByTimer = true;
	}

	LedRgbHelper::Instance()->loop(dayPart);
}

void learn()
{
	BtnLeftHandler.Learn(&irrecv, &Lcd);

	delay(1000);

	BtnRightHandler.Learn(&irrecv, &Lcd);

	delay(1000);

	BtnOkHandler.Learn(&irrecv, &Lcd);

	delay(1000);

	BtnCancelHandler.Learn(&irrecv, &Lcd);

	delay(1000);
}



#pragma endregion
