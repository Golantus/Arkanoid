#pragma once
#include "MenuStatusEnum.h"
#include "Actor.h"
#include <vector>

enum ButtonType
{
	MENU_BUTTONS_START,
	CONTINUE_BUTTON,
	LEVELS_BUTTON,
	SETTINGS_BUTTON,
	EXIT_BUTTON,
	MENU_BUTTONS_END,
	BACK_BUTTON,
	SETTINGS_BUTTONS_START,
	CHECKBOX_BUTTON,
	FPS_30_BUTTON,
	FPS_60_BUTTON,
	FPS_120_BUTTON,
	FPS_240_BUTTON,
	RES_800X600_BUTTON,
	RES_1280X1024_BUTTON,
	RES_1600X900_BUTTON,
	RES_MAX_BUTTON,
	SETTINGS_BUTTONS_END,
	LEVELS_BUTTONS_START,
	LEVEL1_BUTTON,
	LEVEL2_BUTTON,
	LEVEL3_BUTTON,
	LEVEL4_BUTTON,
	LEVEL5_BUTTON,
	LEVEL6_BUTTON,
	LEVEL7_BUTTON,
	LEVEL8_BUTTON,
	LEVEL9_BUTTON,
	LEVEL10_BUTTON,
	LEVELS_BUTTONS_END,
	BUTTON_TYPE_ENUM_END
};

class Button : public Actor
{
public:
	Button(ButtonType, bool inMainMenu, bool inLevelMenu, bool inSettingsMenu);
	Button();

	ButtonType getType();
	bool isShownOnThisMenu(MenuStatus status);

	virtual void mouseOverEvent();
	void resetMouseOver();
	bool getMousoverAftereffect();
private:
	bool mousoverAftereffect;
	bool inMainMenu;
	bool inLevelMenu;
	bool inSettingsMenu;
	ButtonType type;

	std::vector<SDL_Rect> mouseoverShadingRectangleVector; 
};
