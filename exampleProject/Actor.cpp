#include "Actor.h"


extern SDL_Renderer* rend;
extern SDL_Texture* hitbox_tex;
extern SDL_Window* window;

extern int deltaWidth;
extern int deltaHeight;
extern int realScreenWidth;
extern int realScreenHeight;

Actor::Actor(SDL_Rect textureRect, SDL_Texture* texturePointer) 
    :texture(texturePointer), hitboxRectangle(textureRect)
{
}


Actor::Actor()
    :texture(nullptr), hitboxRectangle({0, 0, 0, 0})
{
}

bool Actor::checkCollisionsWithOtherActor(const Actor& OtherActor) const
{
    if (this->getLeftBorder() < OtherActor.getRightBorder() &&
        this->getRightBorder() > OtherActor.getLeftBorder() &&
        this->getUpperBorder() < OtherActor.getLowerBorder() &&
        this->getLowerBorder() > OtherActor.getUpperBorder())
    {
        return true;
    }
    return false;
}

void Actor::draw() const
{
    double propotionX = (double) realScreenWidth / LOGIC_SCREEN_WIDTH;
    double propotionY = (double) realScreenHeight / LOGIC_SCREEN_HEIGHT;
    SDL_Rect drawRectangle = {hitboxRectangle.x * propotionX + deltaWidth/2, hitboxRectangle.y * propotionY + deltaHeight/2,
                              hitboxRectangle.w * propotionX, hitboxRectangle.h * propotionY};
    SDL_RenderCopy(rend, texture, NULL, &drawRectangle);
}

point Actor::getHitboxCenter() const
{
    double centerX = hitboxRectangle.x + (hitboxRectangle.w / 2);
    double centerY = hitboxRectangle.y + (hitboxRectangle.h / 2);
    return point{ centerX, centerY };
}

SDL_Rect Actor::getHitbox() const
{
    return hitboxRectangle;
}

SDL_Texture* Actor::getTexture() const
{
    return texture;
}

void Actor::setTexture(SDL_Texture* tex)
{
    texture = tex;
}

void Actor::setHitbox(SDL_Rect hitboxRect)
{
    hitboxRectangle = hitboxRect;
}

void Actor::setXCoordinate(int coordinate)
{
    hitboxRectangle.x = coordinate;
}

void Actor::setYCoordinate(int coordinate)
{
    hitboxRectangle.y = coordinate;
}

void Actor::setWidth(int width)
{
    hitboxRectangle.w = width;
}

void Actor::setHeight(int height)
{
    hitboxRectangle.h = height;
}

int Actor::getWidth() const
{
    return hitboxRectangle.w;
}

int Actor::getHeight() const
{
    return hitboxRectangle.h;
}

int Actor::getRightBorder() const
{
    return hitboxRectangle.x+hitboxRectangle.w;
}

int Actor::getLeftBorder() const
{
    return hitboxRectangle.x;
}

int Actor::getUpperBorder() const
{
    return hitboxRectangle.y;
}

int Actor::getLowerBorder() const
{
    return hitboxRectangle.y+hitboxRectangle.h;
}