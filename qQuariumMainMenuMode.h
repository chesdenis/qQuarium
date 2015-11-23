#include "qQuariumMode.h"
#include "qQuariumSetupTimeMode.h"
#include "qQuariumTemperatureMode.h"
#include "qQuariumLEDSetupMode.h"
#include "qQuariumSetupDateMode.h"
#include "qQuariumDevicesMode.h"
#include "qQuariumRoomClimateMode.h"

class qQuariumMainMenuMode :
	public qQuariumMode
{
	enum MenuItemsValues
	{
		Info, 
		SetupTime,
		SetupDate,
		Temperature,
		Climate,
		BackLight,
		Devices
	};

private:
	int currentMenuItemId = 0;
	int lastMenuIndex = 6;
	char* getMenuItemTextById(int menuItemId);
public:
	qQuariumSetupTimeMode* setupTimeModeLink = NULL;
	qQuariumSetupDateMode* setupDateModeLink = NULL;
	qQuariumTemperatureMode* temperatureModeLink = NULL;
	qQuariumRoomClimateMode* climateModeLink = NULL;
	qQuariumLEDSetupMode* ledSetupModeLink = NULL;
	qQuariumDevicesMode* devicesModeLink = NULL;

	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();                                                                                                                                                                      
	void RightClick();
	
};
