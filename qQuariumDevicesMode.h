#pragma once
#include "qQuariumMode.h"
#include "BaseOnOfDeviceHelper.h"
class qQuariumDevicesMode :
	public qQuariumMode
{
private:

	int modeLastIndex = 0;
	enum Mode
	{
		View
	};

	Mode CurrentMode = View;

	int deviceCategoryLastIndex = 4;
	enum DeviceCategory
	{
		
		MainLight,
		Aeration,
		Compressor,
		Vulcanius,
		Pump
	};

	DeviceCategory CurrentDeviceCategory = MainLight;

	char* headerDeviceCategoryText = NULL;

	BaseOnOfDeviceHelper* GetDeviceHelper();

public:
	void loop();
	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
};

