#include "inactiveButton.h"
#define INACTIVE_BUTTON_LIST
#include "TextureList.h"

InactiveButton::InactiveButton(ButtonType type, bool inMainMenu, bool inLevelMenu, bool inSettingsMenu)
	:Button( type,  inMainMenu ,  inLevelMenu , inSettingsMenu)
{
	activeTexture = getTexture();

	switch (type)
	{
	case CONTINUE_BUTTON:
		inactiveTexture = continueButtonInactiveTexture;
		break;
	case LEVEL1_BUTTON:
		inactiveTexture = level1ButtonInactiveTexture;
		break;
	case LEVEL2_BUTTON:
		inactiveTexture = level2ButtonInactiveTexture;
		break;
	case LEVEL3_BUTTON:
		inactiveTexture = level3ButtonInactiveTexture;
		break;
	case LEVEL4_BUTTON:
		inactiveTexture = level4ButtonInactiveTexture;
		break;
	case LEVEL5_BUTTON:
		inactiveTexture = level5ButtonInactiveTexture;
		break;
	case LEVEL6_BUTTON:
		inactiveTexture = level6ButtonInactiveTexture;
		break;
	case LEVEL7_BUTTON:
		inactiveTexture = level7ButtonInactiveTexture;
		break;
	case LEVEL8_BUTTON:
		inactiveTexture = level8ButtonInactiveTexture;
		break;
	case LEVEL9_BUTTON:
		inactiveTexture = level9ButtonInactiveTexture;
		break;
	case LEVEL10_BUTTON:
		inactiveTexture = level10ButtonInactiveTexture;
		break;
	case CHECKBOX_BUTTON:
		inactiveTexture = checkboxInactive;
		break;
	case FPS_30_BUTTON:
		inactiveTexture = fps30ButtonInactive;
		break;
	case FPS_60_BUTTON:
		inactiveTexture = fps60ButtonInactive;
		break;
	case FPS_120_BUTTON:
		inactiveTexture = fps120ButtonInactive;
		break;
	case FPS_240_BUTTON:
		inactiveTexture = fps240ButtonInactive;
		break;
	case RES_800X600_BUTTON:
		inactiveTexture = res800x600ButtonInactive;
		break;
	case RES_1280X1024_BUTTON:
		inactiveTexture = res1280x1024ButtonInactive;
		break;
	case RES_1600X900_BUTTON:
		inactiveTexture = res1600x900ButtonInactive;
		break;
	case RES_MAX_BUTTON:
		inactiveTexture = resMaxButtonInactive;
		break;
	default:
		inactiveTexture = nullptr;
		break;
	}
}

void InactiveButton::switchTexture()
{
	if (getTexture() == activeTexture)
		setTexture(inactiveTexture);
	else
		setTexture(activeTexture);
}

void InactiveButton::mouseOverEvent()
{
	if (inactiveTexture == checkboxInactive)
		Button::mouseOverEvent();
	if (getTexture() == inactiveTexture)
		return;
	else
		Button::mouseOverEvent();
}

bool InactiveButton::isActive() const
{
	return getTexture() == activeTexture;
}
