#pragma once
#include "Arduino.h"

class RGBColorHelper
{
public:
	
	int RedPart;
	int GreenPart;
	int BluePart;
	int Brightness;
	char* Title;

	void SetAllComponentToZero();

	void IncrementBright();
	void DecrementBright();

	void Increment(int* partToChange);
	void Decrement(int* partToChange);
	String GetPrintComponentValue(int* partToPrint);

	RGBColorHelper(char* title);
	RGBColorHelper(int redPart, int greenPart, int bluePart, int brightness);
	~RGBColorHelper();
};

