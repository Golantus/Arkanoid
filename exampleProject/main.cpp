#include <ctime> 
#include "GameMenu.h"
#include "Logic_screen_size.h"

SDL_Renderer* rend = NULL;
SDL_Window* window = NULL;

int realScreenWidth = 1600;
int realScreenHeight = 900;
int deltaWidth = 0;
int deltaHeight = 0;

void loadTextures();
void deleteTextures();

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(0)));

    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, realScreenWidth, realScreenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);
        }
        SDL_FreeSurface(screenSurface);
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(window, -1, render_flags);

    loadTextures();

    GameMenu gameMenu;
    gameMenu.startMenuLoop();


    deleteTextures();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

