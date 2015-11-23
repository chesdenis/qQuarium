#include "RGBColorHelper.h"
#include "Arduino.h"

RGBColorHelper::RGBColorHelper(char* title)
{
	Title = title;

	RedPart = 0;
	GreenPart = 0;
	BluePart = 0;
	Brightness = 0;
}

RGBColorHelper::RGBColorHelper(int redPart, int greenPart, int bluePart, int brightness)
{
	RedPart = redPart;
	GreenPart = greenPart;
	BluePart = bluePart;
	Brightness = brightness;
}


RGBColorHelper::~RGBColorHelper()
{
}

String RGBColorHelper::GetPrintComponentValue(int* partToPrint)
{
	int value = *partToPrint;
	String valueAsString = String(value);

	if (value == 0)
	{
		return String("000");
	}
	else if (value < 10)
	{
		return String("00" + valueAsString);
	}
	else if (value < 100)
	{
		return String("0" + valueAsString);
	}
	else
	{
		return valueAsString;
	}
}

void RGBColorHelper::SetAllComponentToZero()
{
	RedPart = 0;
	BluePart = 0;
	GreenPart = 0;
	Brightness = 0;
};

void RGBColorHelper::IncrementBright()
{
	Brightness+=10;
	if (Brightness > 255)
	{
		Brightness = 0;
	}
};

void RGBColorHelper::DecrementBright()
{
	Brightness -= 10;
	if (Brightness < 0)
	{
		Brightness = 255;
	}
};


void RGBColorHelper::Increment(int* partToChange)
{
	(*partToChange)++;
	if ((*partToChange) > 255)
	{
		(*partToChange) = 0;
	}
};

void RGBColorHelper::Decrement(int* partToChange)
{
	(*partToChange)--;
	if ((*partToChange) < 0)
	{
		(*partToChange) = 255;
	}
};
