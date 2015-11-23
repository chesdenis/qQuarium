#pragma once
#include "Arduino.h"
class BaseOnOfDeviceHelper
{
protected:
	uint8_t PinNum;
	virtual void HandleState();

public:
	bool IsActive = false;

	virtual void Init(uint8_t pinNum);
	virtual void Start();
	virtual void Stop();
	virtual void Toggle();


};

