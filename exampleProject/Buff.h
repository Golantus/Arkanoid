#pragma once
#include "MoveableActor.h"
#include "BuffListEnum.h"

class Buff : public MoveableActor
{
public:
	Buff(SDL_Rect hitboxRect, BuffType type);
	BuffType getType();
	bool isBelowScreen();
	bool isApplyingToPlatform();
	double getDuration();
private:
	bool applyingToPlatform;
	BuffType myType;
	double duration;
};