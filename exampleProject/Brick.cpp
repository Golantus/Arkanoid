#include "Brick.h"
#define BRICK_TEX_LIST
#include "TextureList.h"

Brick::Brick(SDL_Rect textureRect, BrickTypeEnum type)
	:brickType(type), isDestroyed(0), canBeBroken(0)
{
	if(brickType == BLUE_BRICK)
		canBeBroken = 1;
	setHitbox(textureRect);
	switch (type)
	{
	case BLUE_BRICK:
		setTexture(blueBrickTexture);
		break;
	case RED_BRICK:
		setTexture(redBrickTexture);
		break;
	case YELLOW_BRICK:
		setTexture(yellowBrickTexture);
		break;
	case GRAY_BRICK:
		setTexture(grayBrickTexture);
		break;
	default:
		break;
	}
}

BrickTypeEnum Brick::getType()
{
	return brickType;
}

bool Brick::getDestroyed()
{
	return isDestroyed;
}

void Brick::reset()
{
	isDestroyed = 0;
	canBeBroken = 0;
	if (brickType == BLUE_BRICK)
		canBeBroken = 1;
	if (brickType == YELLOW_BRICK)
		setTexture(yellowBrickTexture);
}

bool Brick::getCanBeBroken()
{
	return canBeBroken;
}

void Brick::setCanBeBroken()
{
	if (brickType != GRAY_BRICK)
	{
		canBeBroken = 1;
	}
}

void Brick::brickGetHit()
{
	if (getCanBeBroken())
	{
		isDestroyed = 1;
	}
	else if (brickType == YELLOW_BRICK)
	{
		setTexture(yellowBrickDamagedTexture);
		setCanBeBroken();
	}
}

void Brick::destroyBrick()
{
	isDestroyed = 1;
}
