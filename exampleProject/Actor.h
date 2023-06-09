#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Logic_screen_size.h"

class Actor
{
private:
	SDL_Texture* texture;
	SDL_Rect hitboxRectangle;

public:
	Actor(SDL_Rect textureRect, SDL_Texture* texturePointer);
	Actor();

	virtual bool checkCollisionsWithOtherActor(const Actor& other) const;

	void draw() const;

	void setTexture(SDL_Texture* tex);
	void setHitbox(SDL_Rect hitboxRect);
	void setXCoordinate(int coordinate);
	void setYCoordinate(int coordinate);
	void setWidth(int width);
	void setHeight(int height);

	int getWidth() const;
	int getHeight() const;
	int getRightBorder() const;
	int getLeftBorder() const;
	int getUpperBorder() const;
	int getLowerBorder() const;
	point getHitboxCenter() const;
	SDL_Rect getHitbox() const;
	SDL_Texture* getTexture() const;

};
