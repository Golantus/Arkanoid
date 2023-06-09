#pragma once
#include <vector>
#include <string>
#include "inactiveButton.h"
#include "Level.h"


class GameMenu
{
public:
	GameMenu();
	~GameMenu();
	void startMenuLoop();
private:
	MenuStatus status;
	SDL_Rect FullscreenRect;

	Actor menuBackgroundScreen;

	std::unique_ptr<Level> currentLevel;
	std::vector<Button*> buttonVector;
	std::string settingsPath;
	std::string levelSettingsPath;

	bool hasWon;
	bool readyToClose;
	Uint32 fullScreen;

	//FPS and time management variables
	unsigned int FPS;
	double timeForOneFrame;
	Uint64 NOW;
	Uint64 LAST;
	double tickTime; 
	//

	void renderMenu();
	void renderButtons();
	
	void setLevel(ButtonType levelButton);
	
	void eventManagement(std::list<myEventTypes>& events);
	bool checkMouseOverButton(point mouseState);
	void clickHandler(point mouseState);
	
	void resetLevelAfterCompletion();
	
	void setFPS(ButtonType FPSButton);
	void setResolution(ButtonType resButton);
	void setFullscreen(Uint32 fullscreen);
	void updateScreen();
	
	void buttonSetup();
	void loadSettingsFromFile();
	void updateSettings();
	void updateAvailableLevelSettings(LevelNumberEnum number);
};