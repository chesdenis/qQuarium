#pragma once
#include "Arduino.h"
#include "BaseOnOfDeviceHelper.h"
class PumpHelper:
	public BaseOnOfDeviceHelper
{
private:
	PumpHelper(){};
	PumpHelper(PumpHelper const&){};
	PumpHelper& operator=(PumpHelper const&){};
	static PumpHelper* m_pInstance;
	
public:
	static PumpHelper* Instance();
};