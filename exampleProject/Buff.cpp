#include "Buff.h"
#include "RNGFunc.h"
#include "Logic_screen_size.h"

#define BUFF_TEX_LIST
#include "TextureList.h"


Buff::Buff(SDL_Rect hitboxRect, BuffType type)
	:myType(type)
{
	applyingToPlatform = 0;
	duration = 0;
	switch (myType)
	{
	case BONUS_BALL_BUFF:
		setTexture(bonusBallBuffTexture);
		break;
	case EXTRA_LIFE_BUFF:
		setTexture(extraLifeBuffTexture);
		break;
	case EXPAND_PLATFORM:
		setTexture(expandPlatformBuffTexture);
		applyingToPlatform = 1;
		duration = 10;
		break;
	case LASER_GUN:
		setTexture(laserGunBuffTexture);
		applyingToPlatform = 1;
		duration = 5;
		break;
	case CATCH_THE_BALL:
		setTexture(catchTheBallBuffTexture);
		applyingToPlatform = 1;
		duration = 10;
		break;
	}

	setSpeed(20);
	setMovementVector({ 0, 10 });
	setHitbox(hitboxRect);
}

bool Buff::isBelowScreen()
{
	if (getUpperBorder() > LOGIC_SCREEN_HEIGHT)
		return true;

	return false;
}

BuffType Buff::getType()
{
	return myType;
}

bool Buff::isApplyingToPlatform()
{
	return applyingToPlatform;
}

double Buff::getDuration()
{
	return duration;
}

