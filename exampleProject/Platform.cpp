#include "Platform.h"


Platform::Platform(SDL_Texture* texturePointer) 
    :MoveableActor(SDL_Rect { 700, 750,200, 50 }, texturePointer), 
     readyToCatchBall(0),
     initialWidth(getWidth())
{
    setSpeed(5);
    for (int i = 0; i < 3; i++)
    {
        buffApplied[i] = 0;
        buffTimer[i] = 0;
    }
}

Platform::~Platform() 
{
}

int Platform::movePlatform(double tickTime, bool goToRight) //returns the actual X change in pixels
{
    vector2D movVec = { 0, 0 };
    if(goToRight)
        movVec.x =  getWidth();
    else
        movVec.x = -getWidth();

    int oldX = getLeftBorder();
    setMovementVector(movVec);
    move(tickTime);

    if (getRightBorder() >= LOGIC_SCREEN_WIDTH)
    {
        setXCoordinate(LOGIC_SCREEN_WIDTH - getWidth());
    }
    if (getLeftBorder() <= 0)
    {
        setXCoordinate(0);
    }
    int newX = getLeftBorder();

    return newX-oldX;
}

void Platform::buffReset()
{
    if(buffApplied[CATCH_THE_BALL] == 0)
        setReadyToCatchBall(0);

    if (buffApplied[EXPAND_PLATFORM] == 0)
    {
        int deltaWidth = getWidth() - initialWidth;
        int newXCoordinate = getLeftBorder();
        if (deltaWidth > 0)
            newXCoordinate += deltaWidth / 2;
        else
            newXCoordinate -= deltaWidth / 2;
        setXCoordinate(newXCoordinate);

        setWidth(initialWidth);
    }
}

void Platform::buffUpdate(double tickTime)
{
    for (int i = 0; i < 3; i++)
    {
        if (buffApplied[i])
        {
            buffTimer[i] -= tickTime;
            if (buffTimer[i] <= 0)
            {
                buffTimer[i] = 0;
                buffApplied[i] = 0;
                buffReset();
            }
        }
    }
}

bool Platform::isReadyToCatchBall()
{
    return readyToCatchBall;
}

void Platform::setReadyToCatchBall(bool ready)
{
    readyToCatchBall = ready;
}

bool Platform::canShootProjectile()
{
    return buffApplied[LASER_GUN];
}

void Platform::applyBuff(BuffType type, double duration)
{
    if (type >= EXPAND_PLATFORM && type <= CATCH_THE_BALL)
    {
        buffApplied[type] = 1;
        buffTimer[type] = duration;
    }
    if (type == CATCH_THE_BALL)
    {
        setReadyToCatchBall(1);
        buffReset();
    }
    if (type == EXPAND_PLATFORM && getWidth() == initialWidth)
    {
        SDL_Rect newHitbox = getHitbox();
        newHitbox.x -= (newHitbox.w / 1.5)/2;
        newHitbox.w *= 1.5;
        setHitbox(newHitbox);
        movePlatform(0, 0);
    }
}

void Platform::reset(point startCoordinates) {
    buffUpdate(15);
    buffReset();
    setXCoordinate(startCoordinates.x);
    setYCoordinate(startCoordinates.y);
}
