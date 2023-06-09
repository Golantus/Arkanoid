#pragma once
#include "Button.h"

class InactiveButton : public Button
{
public:
	InactiveButton(ButtonType type, bool inMainMenu = 0, bool inLevelMenu = 0, bool inSettingsMenu = 0);
	void switchTexture();
	void mouseOverEvent() override;
	bool isActive() const;
private:
	SDL_Texture* inactiveTexture;
	SDL_Texture* activeTexture;
};