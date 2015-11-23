#include "ButtonHandler.h"
#include "BeepHelper.h"
#include "LcdBackLightHelper.h"
#include "LiquidCrystal.h"


void ButtonHandler::Init(qQuariumMode** currentModeLinkLink)
{
	CurrentModeLinkLink = currentModeLinkLink;
	isCurrentModeLinkDefined = true;
}

void ButtonHandler::Handle(decode_results* irResultsLink)
{
	if (irResultsLink->value == irRemoteButtonId) 
	{
		BtnClick();
		delay(100);
		BeepHelper::Instance()->beep(500, 100);
		LcdBackLightHelper::Instance()->IncreaseLedTime();
	}
	
}

void ButtonHandler::BtnClick()
{
	if (isCurrentModeLinkDefined)
	{
		switch (ButtonType)
		{
		case ButtonHandler::Ok: (*CurrentModeLinkLink)->OkClick();
			break;
		case ButtonHandler::Cancel: (*CurrentModeLinkLink)->CancelClick();
			break;
		case ButtonHandler::Left: (*CurrentModeLinkLink)->LeftClick();
			break;
		case ButtonHandler::Right: (*CurrentModeLinkLink)->RightClick();
			break;
		}
		
	}

	
}

void ButtonHandler::Learn(IRrecv* irrecvLink, LiquidCrystal* lcdLink)
{
	irrecvLink->enableIRIn();
	decode_results irDecodeResults;

	lcdLink->clear();
	switch (ButtonType)
	{
	case ButtonHandler::Ok: lcdLink->print("Press OK...");
		break;
	case ButtonHandler::Cancel: lcdLink->print("Press Cancel...");
		break;
	case ButtonHandler::Left: lcdLink->print("Press Left...");
		break;
	case ButtonHandler::Right: lcdLink->print("Press Right...");
		break;
	}

	while (true) {
		if (irrecvLink->decode(&irDecodeResults)) {
						
			irrecvLink->resume();

			if (irDecodeResults.bits >= 16 && 
				irDecodeResults.value != 0xC53A9966// fix for Pioneer DVD
				) {
			
				lcdLink->setCursor(0, 1);
				lcdLink->print(irDecodeResults.value, HEX);
				irRemoteButtonId = irDecodeResults.value;
				
				BeepHelper::Instance()->beep(500, 100);


				break;
			}


		}
	}

}

ButtonHandler::ButtonHandler(HandlerType buttonType)
{
	ButtonType = buttonType;
}