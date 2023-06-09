#pragma once

#ifdef MENU_TEX_LIST
#define MENU_TEX
	extern SDL_Texture* mainMenuBackgroundTexture;
	extern SDL_Texture* levelMenuBackgroundTexture;
	extern SDL_Texture* settingsMenuBackgroundTexture;

	extern SDL_Texture* loseScreenTexture;
	extern SDL_Texture* winScreenTexture;
#endif // MENU_TEX

#ifdef BUTTON_TEX_LIST
#define BUTTON_TEX
	extern SDL_Texture* backButtonActiveTexture;
	extern SDL_Texture* continueButtonActiveTexture;
	extern SDL_Texture* exitButtonActiveTexture;
	extern SDL_Texture* levlesButtonActiveTexture;
	extern SDL_Texture* settingsButtonActiveTexture;

	extern SDL_Texture* checkboxActive;

	extern SDL_Texture* fps30ButtonActive;
	extern SDL_Texture* fps60ButtonActive;
	extern SDL_Texture* fps120ButtonActive;
	extern SDL_Texture* fps240ButtonActive;

	extern SDL_Texture* res800x600ButtonActive;
	extern SDL_Texture* res1280x1024ButtonActive;
	extern SDL_Texture* res1600x900ButtonActive;
	extern SDL_Texture* resMaxButtonActive;

	extern SDL_Texture* level1ButtonActiveTexture;
	extern SDL_Texture* level2ButtonActiveTexture;
	extern SDL_Texture* level3ButtonActiveTexture;
	extern SDL_Texture* level4ButtonActiveTexture;
	extern SDL_Texture* level5ButtonActiveTexture;
	extern SDL_Texture* level6ButtonActiveTexture;
	extern SDL_Texture* level7ButtonActiveTexture;
	extern SDL_Texture* level8ButtonActiveTexture;
	extern SDL_Texture* level9ButtonActiveTexture;
	extern SDL_Texture* level10ButtonActiveTexture;
	
#endif // BUTTON_TEX

#ifdef INACTIVE_BUTTON_LIST
#define INACTIVE_BUTTON
	extern SDL_Texture* level1ButtonInactiveTexture;
	extern SDL_Texture* level2ButtonInactiveTexture;
	extern SDL_Texture* level3ButtonInactiveTexture;
	extern SDL_Texture* level4ButtonInactiveTexture;
	extern SDL_Texture* level5ButtonInactiveTexture;
	extern SDL_Texture* level6ButtonInactiveTexture;
	extern SDL_Texture* level7ButtonInactiveTexture;
	extern SDL_Texture* level8ButtonInactiveTexture;
	extern SDL_Texture* level9ButtonInactiveTexture;
	extern SDL_Texture* level10ButtonInactiveTexture;

	extern SDL_Texture* continueButtonInactiveTexture;

	extern SDL_Texture* checkboxInactive;

	extern SDL_Texture* fps30ButtonInactive;
	extern SDL_Texture* fps60ButtonInactive;
	extern SDL_Texture* fps120ButtonInactive;
	extern SDL_Texture* fps240ButtonInactive;

	extern SDL_Texture* res800x600ButtonInactive;
	extern SDL_Texture* res1280x1024ButtonInactive;
	extern SDL_Texture* res1600x900ButtonInactive;
	extern SDL_Texture* resMaxButtonInactive;
#endif // INACTIVE_BUTTON_LIST

#ifdef LEVEL_TEX_LIST
#define LEVEL_TEX
	extern SDL_Texture* heartSymbolTexture;

	extern SDL_Texture* platformTexture;

	extern SDL_Texture* ballTexture;

	extern SDL_Texture* levelBackgroundTexture1;
	extern SDL_Texture* levelBackgroundTexture2;
	extern SDL_Texture* levelBackgroundTexture3;
#endif // LEVEL_TEX_LIST

#ifdef BRICK_TEX_LIST
#define BRICK_TEX
	extern SDL_Texture* blueBrickTexture;
	extern SDL_Texture* redBrickTexture;
	extern SDL_Texture* yellowBrickTexture;
	extern SDL_Texture* yellowBrickDamagedTexture;
	extern SDL_Texture* grayBrickTexture;
#endif // BRICK_TEX_LIST

#ifdef BUFF_TEX_LIST
#define BUFF_TEX
	extern SDL_Texture* laserGunBuffTexture;
	extern SDL_Texture* extraLifeBuffTexture;
	extern SDL_Texture* expandPlatformBuffTexture;
	extern SDL_Texture* catchTheBallBuffTexture;
	extern SDL_Texture* bonusBallBuffTexture;
#endif // BUFF_TEX_LIST

	

