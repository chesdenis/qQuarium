#pragma once
#include "Arduino.h"

class BeepHelper
{
private:
	BeepHelper(){};
	BeepHelper(BeepHelper const&){};
	BeepHelper& operator=(BeepHelper const&){};
	static BeepHelper* m_pInstance;

	uint8_t BeepPinNum;

public:

	static BeepHelper* Instance();

	void beep(int freq, unsigned long duration);
	void setup(uint8_t beepPinNum);
};

