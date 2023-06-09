#include "Button.h"
#define BUTTON_TEX_LIST
#include "TextureList.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern int realScreenWidth;
extern int realScreenHeight;
extern SDL_Renderer* rend;
extern int deltaWidth;
extern int deltaHeight;

Button::Button(ButtonType type, bool inMainMenu = 0, bool inLevelMenu = 0, bool inSettingsMenu = 0)
	:type(type), mouseoverShadingRectangleVector(10), inMainMenu(inMainMenu), inLevelMenu(inLevelMenu), inSettingsMenu(inSettingsMenu), mousoverAftereffect(0)
{
	switch (type)
	{
	case CONTINUE_BUTTON:
		setTexture(continueButtonActiveTexture);
		break;
	case LEVELS_BUTTON:
		setTexture(levlesButtonActiveTexture);
		break;
	case SETTINGS_BUTTON:
		setTexture(settingsButtonActiveTexture);
		break;
	case EXIT_BUTTON:
		setTexture(exitButtonActiveTexture);
		break;
	case BACK_BUTTON:
		setTexture(backButtonActiveTexture);
		this->inLevelMenu = 1;
		this->inSettingsMenu = 1;
		break;
	case CHECKBOX_BUTTON:
		setTexture(checkboxActive);
		break;
	case FPS_30_BUTTON:
		setTexture(fps30ButtonActive);
		break;
	case FPS_60_BUTTON:
		setTexture(fps60ButtonActive);
		break;
	case FPS_120_BUTTON:
		setTexture(fps120ButtonActive);
		break;
	case FPS_240_BUTTON:
		setTexture(fps240ButtonActive);
		break;
	case RES_800X600_BUTTON:
		setTexture(res800x600ButtonActive);
		break;
	case RES_1280X1024_BUTTON:
		setTexture(res1280x1024ButtonActive);
		break;
	case RES_1600X900_BUTTON:
		setTexture(res1600x900ButtonActive);
		break;
	case RES_MAX_BUTTON:
		setTexture(resMaxButtonActive);
		break;
	case LEVEL1_BUTTON:
		setTexture(level1ButtonActiveTexture);
		break;
	case LEVEL2_BUTTON:
		setTexture(level2ButtonActiveTexture);
		break;
	case LEVEL3_BUTTON:
		setTexture(level3ButtonActiveTexture);
		break;
	case LEVEL4_BUTTON:
		setTexture(level4ButtonActiveTexture);
		break;
	case LEVEL5_BUTTON:
		setTexture(level5ButtonActiveTexture);
		break;
	case LEVEL6_BUTTON:
		setTexture(level6ButtonActiveTexture);
		break;
	case LEVEL7_BUTTON:
		setTexture(level7ButtonActiveTexture);
		break;
	case LEVEL8_BUTTON:
		setTexture(level8ButtonActiveTexture);
		break;
	case LEVEL9_BUTTON:
		setTexture(level9ButtonActiveTexture);
		break;
	case LEVEL10_BUTTON:
		setTexture(level10ButtonActiveTexture);
		break;
	default:
		setTexture(nullptr);
		break;
	}
}

Button::Button()
	:mouseoverShadingRectangleVector(10), mousoverAftereffect(0), inMainMenu(0), inLevelMenu(0), inSettingsMenu(0), type(BUTTON_TYPE_ENUM_END)
{

}

bool Button::isShownOnThisMenu(MenuStatus status)
{
	if (this == nullptr)
		return 0;
	switch (status)
	{
	case MAIN_MENU:
		return inMainMenu;
		break;
	case LEVEL_MENU:
		return inLevelMenu;
		break;
	case SETTINGS_MENU:
		return inSettingsMenu;
		break;
	case INGAME_STATUS:
		return false;
		break;
	default:
		return false;
		break;
	}
}

bool Button::getMousoverAftereffect()
{
	return mousoverAftereffect;
}

void Button::resetMouseOver()
{
	mousoverAftereffect = 0;
}

void Button::mouseOverEvent()
{
	mousoverAftereffect = 1;

	int numberOfPixelsToIntend = MAX((realScreenWidth / 200), 1);

	double propotionX = (double)realScreenWidth / LOGIC_SCREEN_WIDTH;
	double propotionY = (double)realScreenHeight / LOGIC_SCREEN_HEIGHT;
	SDL_Rect drawRectangle = { getHitbox().x * propotionX + deltaWidth / 2, getHitbox().y * propotionY + deltaHeight / 2,
							  getHitbox().w * propotionX, getHitbox().h * propotionY };

	mouseoverShadingRectangleVector[0] = drawRectangle;
	for (int i = 1; i < 10; i++)
	{
		mouseoverShadingRectangleVector[i] = { drawRectangle.x + i , drawRectangle.y + i , drawRectangle.w - i * 2, drawRectangle.h - i * 2 };
	}
	SDL_RenderDrawRects(rend, &mouseoverShadingRectangleVector[0], numberOfPixelsToIntend);

	SDL_RenderPresent(rend);
}

ButtonType Button::getType()
{
	return type;
}
