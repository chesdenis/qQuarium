#include "BaseOnOfDeviceHelper.h"


void BaseOnOfDeviceHelper::Init(uint8_t pinNum)
{
	PinNum = pinNum;
	pinMode(PinNum, OUTPUT);
}

void BaseOnOfDeviceHelper::Start()
{
	IsActive = true;
	HandleState();
}

void BaseOnOfDeviceHelper::Stop()
{
	IsActive = false;
	HandleState();
}

void BaseOnOfDeviceHelper::Toggle()
{
	IsActive = !IsActive;
	HandleState();
}

void BaseOnOfDeviceHelper::HandleState()
{
	if (IsActive)
	{
		digitalWrite(PinNum, HIGH);
	}
	else
	{
		digitalWrite(PinNum, LOW);
	}
}
