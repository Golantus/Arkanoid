#include <SDL_image.h>
#include <list>
#include <iostream>

extern SDL_Renderer* rend;

std::list<SDL_Texture*> textureList;

SDL_Texture* mainMenuBackgroundTexture;
SDL_Texture* levelMenuBackgroundTexture;
SDL_Texture* settingsMenuBackgroundTexture;

SDL_Texture* backButtonActiveTexture;
SDL_Texture* continueButtonActiveTexture;
SDL_Texture* continueButtonInactiveTexture;
SDL_Texture* exitButtonActiveTexture; 
SDL_Texture* levlesButtonActiveTexture; 
SDL_Texture* settingsButtonActiveTexture;

SDL_Texture* checkboxActive;
SDL_Texture* checkboxInactive;

SDL_Texture* fps30ButtonActive;
SDL_Texture* fps60ButtonActive;
SDL_Texture* fps120ButtonActive;
SDL_Texture* fps240ButtonActive;

SDL_Texture* fps30ButtonInactive;
SDL_Texture* fps60ButtonInactive;
SDL_Texture* fps120ButtonInactive;
SDL_Texture* fps240ButtonInactive;

SDL_Texture* res800x600ButtonActive;
SDL_Texture* res1280x1024ButtonActive;
SDL_Texture* res1600x900ButtonActive;
SDL_Texture* resMaxButtonActive;

SDL_Texture* res800x600ButtonInactive;
SDL_Texture* res1280x1024ButtonInactive;
SDL_Texture* res1600x900ButtonInactive;
SDL_Texture* resMaxButtonInactive;

SDL_Texture* level1ButtonActiveTexture;
SDL_Texture* level2ButtonActiveTexture;
SDL_Texture* level3ButtonActiveTexture;
SDL_Texture* level4ButtonActiveTexture;
SDL_Texture* level5ButtonActiveTexture;
SDL_Texture* level6ButtonActiveTexture;
SDL_Texture* level7ButtonActiveTexture;
SDL_Texture* level8ButtonActiveTexture;
SDL_Texture* level9ButtonActiveTexture;
SDL_Texture* level10ButtonActiveTexture;

SDL_Texture* level1ButtonInactiveTexture;
SDL_Texture* level2ButtonInactiveTexture;
SDL_Texture* level3ButtonInactiveTexture;
SDL_Texture* level4ButtonInactiveTexture;
SDL_Texture* level5ButtonInactiveTexture;
SDL_Texture* level6ButtonInactiveTexture;
SDL_Texture* level7ButtonInactiveTexture;
SDL_Texture* level8ButtonInactiveTexture;
SDL_Texture* level9ButtonInactiveTexture;
SDL_Texture* level10ButtonInactiveTexture;

SDL_Texture* platformTexture;

SDL_Texture* ballTexture;

SDL_Texture* blueBrickTexture;
SDL_Texture* redBrickTexture;
SDL_Texture* yellowBrickTexture;
SDL_Texture* yellowBrickDamagedTexture;
SDL_Texture* grayBrickTexture;

SDL_Texture* levelBackgroundTexture1;
SDL_Texture* levelBackgroundTexture2;
SDL_Texture* levelBackgroundTexture3;

SDL_Texture* heartSymbolTexture;
SDL_Texture* loseScreenTexture;
SDL_Texture* winScreenTexture;

SDL_Texture* laserGunBuffTexture;
SDL_Texture* extraLifeBuffTexture;
SDL_Texture* expandPlatformBuffTexture;
SDL_Texture* catchTheBallBuffTexture;
SDL_Texture* bonusBallBuffTexture;



void createTexture(SDL_Texture* &tex, const char* path);

void loadTextures()
{
    createTexture(mainMenuBackgroundTexture, "resource/image/mainMenuBackgroundTexture.png");
    createTexture(levelMenuBackgroundTexture, "resource/image/levelMenuBackgroundTexture.png");
    createTexture(settingsMenuBackgroundTexture, "resource/image/settingsMenuBackgroundTexture.png");

    createTexture(backButtonActiveTexture, "resource/image/backButtonActive.png");
    createTexture(continueButtonActiveTexture, "resource/image/continueButtonActive.png");
    createTexture(continueButtonInactiveTexture, "resource/image/continueButtonInactive.png");
    createTexture(exitButtonActiveTexture, "resource/image/exitButtonActive.png");
    createTexture(levlesButtonActiveTexture, "resource/image/levlesButtonActive.png");
    createTexture(settingsButtonActiveTexture, "resource/image/settingsButtonActive.png");

    createTexture(checkboxActive, "resource/image/checkboxActive.png");
    createTexture(checkboxInactive, "resource/image/checkboxInactive.png");

    createTexture(fps30ButtonActive, "resource/image/fps30Active.png");
    createTexture(fps60ButtonActive, "resource/image/fps60Active.png");
    createTexture(fps120ButtonActive, "resource/image/fps120Active.png");
    createTexture(fps240ButtonActive, "resource/image/fps240Active.png");

    createTexture(fps30ButtonInactive, "resource/image/fps30Inactive.png");
    createTexture(fps60ButtonInactive, "resource/image/fps60Inactive.png");
    createTexture(fps120ButtonInactive, "resource/image/fps120Inactive.png");
    createTexture(fps240ButtonInactive, "resource/image/fps240Inactive.png");

    createTexture(res800x600ButtonActive, "resource/image/res800x600ButtonActive.png");
    createTexture(res1280x1024ButtonActive, "resource/image/res1280x1024ButtonActive.png");
    createTexture(res1600x900ButtonActive, "resource/image/res1600x900ButtonActive.png");
    createTexture(resMaxButtonActive, "resource/image/resMaxButtonActive.png");

    createTexture(res800x600ButtonInactive, "resource/image/res800x600ButtonInactive.png");
    createTexture(res1280x1024ButtonInactive, "resource/image/res1280x1024ButtonInactive.png");
    createTexture(res1600x900ButtonInactive, "resource/image/res1600x900ButtonInactive.png");
    createTexture(resMaxButtonInactive, "resource/image/resMaxButtonInactive.png");

    createTexture(level1ButtonActiveTexture, "resource/image/level1ButtonActive.png");
    createTexture(level2ButtonActiveTexture, "resource/image/level2ButtonActive.png");
    createTexture(level3ButtonActiveTexture, "resource/image/level3ButtonActive.png");
    createTexture(level4ButtonActiveTexture, "resource/image/level4ButtonActive.png");
    createTexture(level5ButtonActiveTexture, "resource/image/level5ButtonActive.png");
    createTexture(level6ButtonActiveTexture, "resource/image/level6ButtonActive.png");
    createTexture(level7ButtonActiveTexture, "resource/image/level7ButtonActive.png");
    createTexture(level8ButtonActiveTexture, "resource/image/level8ButtonActive.png");
    createTexture(level9ButtonActiveTexture, "resource/image/level9ButtonActive.png");
    createTexture(level10ButtonActiveTexture, "resource/image/level10ButtonActive.png");

    createTexture(level1ButtonInactiveTexture, "resource/image/level1ButtonInactive.png");
    createTexture(level2ButtonInactiveTexture, "resource/image/level2ButtonInactive.png");
    createTexture(level3ButtonInactiveTexture, "resource/image/level3ButtonInactive.png");
    createTexture(level4ButtonInactiveTexture, "resource/image/level4ButtonInactive.png");
    createTexture(level5ButtonInactiveTexture, "resource/image/level5ButtonInactive.png");
    createTexture(level6ButtonInactiveTexture, "resource/image/level6ButtonInactive.png");
    createTexture(level7ButtonInactiveTexture, "resource/image/level7ButtonInactive.png");
    createTexture(level8ButtonInactiveTexture, "resource/image/level8ButtonInactive.png");
    createTexture(level9ButtonInactiveTexture, "resource/image/level9ButtonInactive.png");
    createTexture(level10ButtonInactiveTexture, "resource/image/level10ButtonInactive.png");



    createTexture(platformTexture, "resource/image/platformTexture.png");

    createTexture(ballTexture, "resource/image/ballTexture.png");

    createTexture(blueBrickTexture, "resource/image/blueBrickTexture.png");
    createTexture(redBrickTexture, "resource/image/redBrickTexture.png");
    createTexture(yellowBrickTexture, "resource/image/yellowBrickTexture.png");
    createTexture(yellowBrickDamagedTexture, "resource/image/yellowBrickDamagedTexture.png");
    createTexture(grayBrickTexture, "resource/image/grayBrickTexture.png");

    createTexture(levelBackgroundTexture1, "resource/image/levelBackgroundTexture1.png");
    createTexture(levelBackgroundTexture2, "resource/image/levelBackgroundTexture2.png");
    createTexture(levelBackgroundTexture3, "resource/image/levelBackgroundTexture3.png");    

    createTexture(heartSymbolTexture, "resource/image/heartSymbolTexture.png");
    createTexture(loseScreenTexture, "resource/image/loseScreenTexture.png");
    createTexture(winScreenTexture, "resource/image/winScreenTexture.png");


    createTexture(laserGunBuffTexture, "resource/image/laserGunBuffTexture.png");
    createTexture(extraLifeBuffTexture, "resource/image/extraLifeBuffTexture.png");
    createTexture(expandPlatformBuffTexture, "resource/image/expandPlatformBuffTexture.png");
    createTexture(catchTheBallBuffTexture, "resource/image/catchTheBallBuffTexture.png");
    createTexture(bonusBallBuffTexture, "resource/image/bonusBallBuffTexture.png");
}

void createTexture(SDL_Texture* &tex, const char* path)
{
    SDL_Surface* buffer_surface = IMG_Load(path);
    tex = SDL_CreateTextureFromSurface(rend, buffer_surface);
    if (tex == NULL)
        std::cout<< "Texture loading failed, missing texture path is : " << path;
    textureList.push_back(tex);
    SDL_FreeSurface(buffer_surface);
}

void deleteTextures() {
    for (auto& texture : textureList)
    {
        SDL_DestroyTexture(texture);
    }
    textureList.clear();
}