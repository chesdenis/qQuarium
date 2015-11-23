#include "qQuariumRoomClimateMode.h"
#include "RoomTemperature.h"
#include "ClockHelper.h"

qQuariumRoomClimateMode::qQuariumRoomClimateMode()
{

};
qQuariumRoomClimateMode::~qQuariumRoomClimateMode()
{

};

void qQuariumRoomClimateMode::loop()
{
	if (!isLcdUpdated | !ClockHelper::Instance()->isUpdatedByTimer)
	{
		LcdLink->clear();
		LcdLink->setCursor(0, 0);

		LcdLink->print("Temp: ");
		LcdLink->print(RoomTemperature::Instance()->GetTemperatureText());
		LcdLink->print("\x99""C");


		LcdLink->setCursor(0, 1);

		LcdLink->print("Hum: ");
		LcdLink->print(RoomTemperature::Instance()->GetHumidityText());
		LcdLink->print("%");

		isLcdUpdated = true;
	}
};
void qQuariumRoomClimateMode::OkClick()
{
	isLcdUpdated = false;
};
void qQuariumRoomClimateMode::CancelClick()
{
	exit();
};
void qQuariumRoomClimateMode::LeftClick()
{
	isLcdUpdated = false;
};
void qQuariumRoomClimateMode::RightClick()
{
	isLcdUpdated = false;
};
