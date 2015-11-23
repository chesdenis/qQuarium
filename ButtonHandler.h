#pragma once
#include "Arduino.h"
#include "qQuariumMode.h"
#include "IRremote.h"

class ButtonHandler
{
private:
	unsigned long irRemoteButtonId;
	void BtnClick();
protected:
	qQuariumMode** CurrentModeLinkLink;
	bool isCurrentModeLinkDefined = false;

public:
	enum HandlerType { Ok, Cancel, Left, Right };
	HandlerType ButtonType;
	ButtonHandler(HandlerType buttonType);
	void Init(qQuariumMode** currentModeLinkLink);
	void Handle(decode_results* irResultsLink);

	void Learn(IRrecv* irrecvLink, LiquidCrystal* lcdLink);
};

