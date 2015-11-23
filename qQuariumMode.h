#pragma once
#include "LiquidCrystal.h"

class qQuariumMode
{
protected:
	LiquidCrystal* LcdLink;
	qQuariumMode* ParentModeLink;
	qQuariumMode** CurrentModeLinkLink;

	

	bool isUpdateByTimerEnabled = false;
	
	bool isParentModeLinkDefined = false;
	bool isCurrentModeLinkLinkDefined = false;

public:
	bool isLcdUpdated = false;

	void init(LiquidCrystal* lcdLink, qQuariumMode** currentModeLinkLink);
	void init(LiquidCrystal* lcdLink, qQuariumMode* parentModeLink, qQuariumMode** currentModeLinkLink);
	void init(LiquidCrystal* lcdLink, qQuariumMode* parentModeLink);
	
	void exit();

	virtual void loop();

	virtual void OkClick();
	virtual void CancelClick();
	virtual void LeftClick();
	virtual void RightClick();

};

