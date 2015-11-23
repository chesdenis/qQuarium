#include "qQuariumMode.h"
#include "LiquidCrystal.h"

void qQuariumMode::init(LiquidCrystal* lcdLink, qQuariumMode** currentModeLinkLink)
{
	LcdLink = lcdLink;
	CurrentModeLinkLink = currentModeLinkLink;

	isCurrentModeLinkLinkDefined = true;
}
void qQuariumMode::init(LiquidCrystal* lcdLink, qQuariumMode* parentModeLink, qQuariumMode** currentModeLinkLink)
{
	LcdLink = lcdLink;
	ParentModeLink = parentModeLink;
	CurrentModeLinkLink = currentModeLinkLink;

	isParentModeLinkDefined = true;
	isCurrentModeLinkLinkDefined = true;
};

void qQuariumMode::init(LiquidCrystal* lcdLink, qQuariumMode* parentModeLink)
{
	LcdLink = lcdLink;
	ParentModeLink = parentModeLink;

	isParentModeLinkDefined = true;

}

void qQuariumMode::exit()
{
	isLcdUpdated = false;
	if (isCurrentModeLinkLinkDefined & isParentModeLinkDefined)
	{
		*CurrentModeLinkLink = ParentModeLink;
		(*CurrentModeLinkLink)->isLcdUpdated = false;
	}
}
