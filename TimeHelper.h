#pragma once
#include "Arduino.h"

class TimeHelper
{
	
public:
	int Hours = 0;
	int Minutes = 0;

	char* TimeName = NULL;

	bool isEditMode = false;

	void IncrementHours();
	void DecrementHours();
	void IncrementMinutes();
	void DecrementMinutes();

	String getFormatedTime();
	String getFormatedHours();
	String getFormatedMinutes();


	TimeHelper();
	TimeHelper(char* timeName);
	~TimeHelper();
};

