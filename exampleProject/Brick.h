#pragma once
#include "Actor.h"

enum BrickTypeEnum
{
	BLUE_BRICK = 0, //usual brick
	RED_BRICK = 1, //can be destroyed only if all other-colored bricks are destroyed
	YELLOW_BRICK = 2, //breaks after 2 hits
	GRAY_BRICK = 3 // can not be destroyed
};

class Brick : public Actor
{
public:
    Brick(SDL_Rect textureRect, BrickTypeEnum type);

	BrickTypeEnum getType();
	bool getDestroyed();
	bool getCanBeBroken();
	
	void setCanBeBroken();
	
	void brickGetHit();
	void destroyBrick();

	void reset();
private:
	BrickTypeEnum brickType;
	bool canBeBroken;
	bool isDestroyed;
};