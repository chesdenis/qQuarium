#pragma once
#include "qQuariumMode.h"
class qQuariumRoomClimateMode :
	public qQuariumMode
{
public:
	qQuariumRoomClimateMode();
	~qQuariumRoomClimateMode();

	void loop();

	void OkClick();
	void CancelClick();
	void LeftClick();
	void RightClick();
};

