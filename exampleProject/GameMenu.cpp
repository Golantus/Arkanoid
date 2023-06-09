#include "GameMenu.h"
#include "Logic_screen_size.h"

#include <fstream>
#include <string>

#define MENU_TEX_LIST
#include "TextureList.h"


extern int realScreenWidth;
extern int realScreenHeight;
extern int deltaWidth;
extern int deltaHeight;

extern SDL_Window* window;
extern SDL_Renderer* rend;

GameMenu::GameMenu()
    : 
    menuBackgroundScreen({ 0, 0, 1600, 900 }, mainMenuBackgroundTexture),
    buttonVector(BUTTON_TYPE_ENUM_END), status(MAIN_MENU),
    readyToClose(0), currentLevel(nullptr),
    hasWon(0), 
    settingsPath("settings/settings.txt"),
    levelSettingsPath("settings/maxLevel.txt")
{
    buttonSetup();

    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    tickTime = 0;
    FPS = 120;
    timeForOneFrame = (double(1) / FPS);

    loadSettingsFromFile();

    renderMenu();
}

GameMenu::~GameMenu()
{
    updateSettings();
}

void GameMenu::startMenuLoop()
{
    std::list<myEventTypes> events;
    while (!readyToClose) {

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        tickTime += (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        if (tickTime >= timeForOneFrame) {
            if (tickTime > timeForOneFrame)
                tickTime = timeForOneFrame;

            eventManagement(events);

            if (status == INGAME_STATUS && currentLevel)
            {
                
                int tickResult = currentLevel->tick(tickTime, events);
                events.clear();

                switch (tickResult)
                {
                case 0:
                    break;
                case 1:
                    hasWon = 1;
                    resetLevelAfterCompletion();
                    break;
                case -1:
                    resetLevelAfterCompletion();
                    break;
                default:
                    break;
                }
            }
            tickTime = 0;
        }
    }

    
}

void GameMenu::setLevel(ButtonType levelButton)
{
    LevelNumberEnum number = static_cast<LevelNumberEnum>(levelButton-LEVELS_BUTTONS_START);

    InactiveButton* continueButton = dynamic_cast<InactiveButton*>(buttonVector[CONTINUE_BUTTON]);
    if ( ! continueButton->isActive())
        continueButton->switchTexture();

    bool hasRestarted = 0;
    if (currentLevel)
    {
        if (currentLevel->getLevelNumber() == number)
        {
            currentLevel->restart();
            hasRestarted = 1;
        }
    }

    if (!hasRestarted)
        currentLevel.reset(new Level(number));

    status = INGAME_STATUS;
}

void GameMenu::eventManagement(std::list<myEventTypes>& events)
{
    SDL_Event event;

    int x, y;
    SDL_GetMouseState(&x, &y);
    double propotionX = (double)realScreenWidth / LOGIC_SCREEN_WIDTH;
    double propotionY = (double)realScreenHeight / LOGIC_SCREEN_HEIGHT;
    x /= propotionX;
    y /= propotionY;

    point mouseState((x - (deltaWidth / propotionX) / 2),    (y - (deltaHeight / propotionY) / 2));

    if (status != INGAME_STATUS)
       checkMouseOverButton(mouseState);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            readyToClose = 1;
            return;

        case SDL_MOUSEBUTTONDOWN:
            clickHandler(mouseState);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if (status == MAIN_MENU)
                {
                    readyToClose = 1;
                    return;
                }
                if (status == SETTINGS_MENU)
                    updateSettings();
                if (status == AFTERGAME_STATUS)
                    hasWon = 0;
                if (status == INGAME_STATUS && currentLevel)
                    events.push_back(RELEASED_BOTH);
                status = MAIN_MENU;
                renderMenu();
                break;
            }
            break;
        }
        if (status == INGAME_STATUS && currentLevel)
        {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    events.push_back(PRESSED_A);
                    break;
                case SDLK_d:
                    events.push_back(PRESSED_D);
                    break;
                case SDLK_LEFT:
                    events.push_back(PRESSED_LEFT_ARROW);
                    break;
                case SDLK_RIGHT:
                    events.push_back(PRESSED_RIGHT_ARROW);
                    break;
                case SDLK_ESCAPE:
                    if (status == MAIN_MENU)
                    {
                        readyToClose = 1;
                        return;
                    }
                    status = MAIN_MENU;
                    renderMenu();
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    events.push_back(RELEASED_A);
                    break;
                case SDLK_d:
                    events.push_back(RELEASED_D);
                    break;
                case SDLK_LEFT:
                    events.push_back(RELEASED_LEFT_ARROW);
                    break;
                case SDLK_RIGHT:
                    events.push_back(RELEASED_RIGHT_ARROW);
                    break;
                }
                break;
            }
        }
    }
}

void GameMenu::clickHandler(point mouseState)
{
    if (status == INGAME_STATUS)
    {
        currentLevel->tryToLaunchBall(mouseState);
        return;
    }
    for (auto button : buttonVector)
    {
        if (button->isShownOnThisMenu(status))
        {
            ButtonType thisButtonType = button->getType();
            InactiveButton* inactiveButton = dynamic_cast<InactiveButton*>(buttonVector[thisButtonType]);
            bool isactive = 0;
            if (inactiveButton)
                isactive = inactiveButton->isActive();

            if (coollisionOfRectangleAndPoint(button->getHitbox(), mouseState))
            {
                if (isactive)
                {
                    if (thisButtonType >= FPS_30_BUTTON && thisButtonType <= FPS_240_BUTTON)
                        setFPS(thisButtonType);
                    if (thisButtonType >= RES_800X600_BUTTON && thisButtonType <= RES_MAX_BUTTON)
                        setResolution(thisButtonType);
                    if (thisButtonType >= LEVEL1_BUTTON && thisButtonType <= LEVEL10_BUTTON)
                        setLevel(thisButtonType);
                    renderButtons();
                }
                switch (thisButtonType)
                {
                case(BACK_BUTTON):
                    if(status == SETTINGS_MENU)
                        updateSettings();
                    status = MAIN_MENU;
                    renderMenu();
                    return;
                case(EXIT_BUTTON):
                    readyToClose = 1;
                    return;
                case(LEVELS_BUTTON):
                    status = LEVEL_MENU;
                    renderMenu();
                    return;
                case(SETTINGS_BUTTON):
                    status = SETTINGS_MENU;
                    renderMenu();
                    return;
                case(CONTINUE_BUTTON):
                    if (currentLevel && isactive)
                        status = INGAME_STATUS;
                    return;
                case CHECKBOX_BUTTON:
                    if (isactive)
                        setFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP);
                    else
                        setFullscreen(0);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool GameMenu::checkMouseOverButton(point mouseState)
{
    for (auto button : buttonVector)
    {
        if (button->isShownOnThisMenu(status))
        {
            if (coollisionOfRectangleAndPoint(button->getHitbox(), mouseState))
            {
                button->mouseOverEvent();
            }
            else if (button->getMousoverAftereffect())
            {
                button->resetMouseOver();
                button->draw();
                SDL_RenderPresent(rend);
            }
        }
    }
    return 0;
}

void GameMenu::setFPS(ButtonType FPSButton)
{
    switch (FPSButton)
    {
    case FPS_30_BUTTON:
        FPS = 30;
        break;
    case FPS_60_BUTTON:
        FPS = 60;
        break;
    case FPS_120_BUTTON:
        FPS = 120;
        break;
    case FPS_240_BUTTON:
        FPS = 240;
        break;
    default:
        FPS = 60;
        break;
    }
    timeForOneFrame = (double(1) / FPS);
    for (int i = FPS_30_BUTTON; i<=FPS_240_BUTTON; i++)
    {
        InactiveButton* inactiveButton = dynamic_cast<InactiveButton*>(buttonVector[i]);
        if (i == FPSButton)
        {
            inactiveButton->switchTexture();
            continue;
        }
        if ( ! inactiveButton->isActive())
            inactiveButton->switchTexture();
    }
}

void GameMenu::setResolution(ButtonType resButton)
{
    switch (resButton)
    {
    case RES_800X600_BUTTON:
        realScreenWidth = 800;
        realScreenHeight = 600;
        break;
    case RES_1280X1024_BUTTON:
        realScreenWidth = 1280;
        realScreenHeight = 1024;
        break;
    case RES_1600X900_BUTTON:
        realScreenWidth = 1600;
        realScreenHeight = 900;
        break;
    case RES_MAX_BUTTON:
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_GetWindowSizeInPixels(window, &realScreenWidth, &realScreenHeight);
        if(!fullScreen)
            SDL_SetWindowFullscreen(window, 0);
        break;
    default:
        realScreenWidth = 1600;
        realScreenHeight = 900;
        break;
    }
    for (int i = RES_800X600_BUTTON; i <= RES_MAX_BUTTON; i++)
    {
        InactiveButton* inactiveButton = dynamic_cast<InactiveButton*>(buttonVector[i]);
        if (i == resButton)
        {
            inactiveButton->switchTexture();
            continue;
        }
        if (!inactiveButton->isActive())
            inactiveButton->switchTexture();
    }


    SDL_SetWindowSize(window, realScreenWidth, realScreenHeight);
    SDL_SetWindowBordered(window, SDL_TRUE);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    updateScreen();
}

void GameMenu::setFullscreen(Uint32 fullscreen)
{
    this->fullScreen = fullscreen;
    InactiveButton* button = dynamic_cast<InactiveButton*>(buttonVector[CHECKBOX_BUTTON]);
    if (!fullScreen)
    {
        if (!button->isActive())
            button->switchTexture();
    }
    else
        button->switchTexture();
    SDL_SetWindowFullscreen(window, fullscreen);
    updateScreen();
}

void GameMenu::updateScreen()
{
    if (fullScreen == 0)
    {
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        deltaWidth = 0;
        deltaHeight = 0;
    }
    else if (fullScreen == SDL_WINDOW_FULLSCREEN_DESKTOP)
    {
        int currentWidth, currentHeight;
        SDL_GetWindowSizeInPixels(window, &currentWidth, &currentHeight);
        deltaWidth = currentWidth - realScreenWidth;
        deltaHeight = currentHeight - realScreenHeight;
    }
    renderMenu();
}

void GameMenu::loadSettingsFromFile()
{
    //settings
    std::ifstream file(settingsPath);

    if (!file)
    {
        std::ofstream outFile(settingsPath);
        outFile << 0 << std::endl << 10 << std::endl << 15;
        file.open(settingsPath);
    }
    
    std::string currentString;

    file >> currentString;
    setFullscreen(std::stoi(currentString));

    file >> currentString;
    setFPS(static_cast<ButtonType>(std::stoi(currentString)));

    file >> currentString;
    setResolution(static_cast<ButtonType>(std::stoi(currentString)));

    file.close();

    //available level
    file.open(levelSettingsPath);
    if (!file)
    {
        std::ofstream outFile(levelSettingsPath);
        outFile << 1;
        file.open(levelSettingsPath);
    }

    file >> currentString;
    int levelNumber = std::stoi(currentString);
    for (int i = 1; i <= levelNumber; i++)
    {
        InactiveButton* button = dynamic_cast<InactiveButton*>(buttonVector[LEVELS_BUTTONS_START + i]);
        button->switchTexture();
    }
}

void GameMenu::updateSettings()
{
    std::ofstream outFile(settingsPath);

    std::string fullscreen = std::to_string(fullScreen);
    std::string FPS;
    std::string RESOLUTION;
    for (int i = FPS_30_BUTTON ; i <= FPS_240_BUTTON; i++)
    {
        if (! dynamic_cast<InactiveButton*>(buttonVector[i])->isActive()) 
            FPS = std::to_string(i);
    }
    for (int i = RES_800X600_BUTTON; i <= RES_MAX_BUTTON; i++)
    {
        if (! dynamic_cast<InactiveButton*>(buttonVector[i])->isActive())
            RESOLUTION = std::to_string(i);
    }

   
    outFile << fullscreen << std::endl << FPS << std::endl << RESOLUTION;
}

void GameMenu::updateAvailableLevelSettings(LevelNumberEnum number)
{
    std::fstream inFile(levelSettingsPath);
    std::string currentString;
    inFile >> currentString;
    if (number  >= std::stoi(currentString) && number != 10)
    {
        std::ofstream outFile(levelSettingsPath);
        outFile << number+1;
    }


}

void GameMenu::buttonSetup()
{
    int horizontalIndent = 0, verticalIndent = 120;
    //main menu setup
    for (int i = MENU_BUTTONS_START + 1; i < MENU_BUTTONS_END; i++)
    {
        if (i == CONTINUE_BUTTON)
        {
            buttonVector[i] = new InactiveButton(static_cast<ButtonType>(i), 1, 0, 0);
            dynamic_cast<InactiveButton*>(buttonVector[i])->switchTexture();
        }
        else
            buttonVector[i] = new Button(static_cast<ButtonType>(i), 1, 0, 0);

        point buttonCoordinates(500 + horizontalIndent, 390 + verticalIndent * (i - (MENU_BUTTONS_START + 1)));
        buttonVector[i]->setHitbox({ (int)buttonCoordinates.x,(int)buttonCoordinates.y, 600, 90 });
    }


    buttonVector[BACK_BUTTON] = new Button(BACK_BUTTON, 0, 0, 1);
    buttonVector[BACK_BUTTON]->setHitbox({ 500, 750 , 600, 90 });

    horizontalIndent = 160;
    //settings menu setup
    for (int i = SETTINGS_BUTTONS_START + 1; i < SETTINGS_BUTTONS_END; i++)
    {

        buttonVector[i] = new InactiveButton(static_cast<ButtonType>(i), 0, 0, 1);
        if (i == CHECKBOX_BUTTON)
            buttonVector[i]->setHitbox({ 1060 , 290 , 100, 100 });
        else if (i >= FPS_30_BUTTON && i <= FPS_240_BUTTON)
            buttonVector[i]->setHitbox({ 580 + horizontalIndent * (i - FPS_30_BUTTON) , 410 , 100, 100 });
        else
        {
            buttonVector[i]->setHitbox({ 580 + horizontalIndent * (i - RES_800X600_BUTTON), 520 , 100, 100 });
        }
    }


    //levels menu setup
    horizontalIndent = 175;
    verticalIndent = 150;
    for (int i = LEVELS_BUTTONS_START + 1; i < LEVELS_BUTTONS_END; i++)
    {
        buttonVector[i] = new InactiveButton(static_cast<ButtonType>(i), 0, 1, 0);

        point buttonCoordinates;
        if (buttonVector[i]->getType() <= LEVEL5_BUTTON)
        {
            buttonCoordinates.x = 400 + (horizontalIndent * (i - LEVEL1_BUTTON));
            buttonCoordinates.y = 400;
            buttonVector[i]->setHitbox({ (int)buttonCoordinates.x, (int)buttonCoordinates.y, 100, 75 });
        }
        else
        {
            buttonCoordinates.x = 400 + (horizontalIndent * (i - LEVEL6_BUTTON));
            buttonCoordinates.y = 400 + (verticalIndent);
            buttonVector[i]->setHitbox({ (int)buttonCoordinates.x, (int)buttonCoordinates.y, 100, 75 });
        }
        dynamic_cast<InactiveButton*>(buttonVector[i])->switchTexture();
    }
}


void GameMenu::resetLevelAfterCompletion()
{
    if (hasWon)
    {
        LevelNumberEnum levelNumber = currentLevel->getLevelNumber();
        updateAvailableLevelSettings(levelNumber);
        if (levelNumber < LEVEL10)
        {
            InactiveButton* button = dynamic_cast<InactiveButton*>(buttonVector[LEVEL1_BUTTON + levelNumber]);
            if (!button->isActive())
                button->switchTexture();
        }
    }
    currentLevel.reset(nullptr);
    status = AFTERGAME_STATUS;
    dynamic_cast<InactiveButton*>(buttonVector[CONTINUE_BUTTON])->switchTexture();
    renderMenu();
}

void GameMenu::renderButtons()
{
    for (auto button : buttonVector)
    {
        if (button->isShownOnThisMenu(status))
        {
            button->draw();
        }
    }
    SDL_RenderPresent(rend);
}

void GameMenu::renderMenu()
{
    SDL_RenderClear(rend);
    switch (status)
    {
    case MAIN_MENU:
        menuBackgroundScreen.setTexture(mainMenuBackgroundTexture);
        break;
    case LEVEL_MENU:
        menuBackgroundScreen.setTexture(levelMenuBackgroundTexture);
        break;
    case SETTINGS_MENU:
        menuBackgroundScreen.setTexture(settingsMenuBackgroundTexture);
        break;
    case AFTERGAME_STATUS:
        if (hasWon)
            menuBackgroundScreen.setTexture(winScreenTexture);
        else
            menuBackgroundScreen.setTexture(loseScreenTexture);
        break;
    default:
        break;
    }
    menuBackgroundScreen.draw();
    renderButtons();
}
