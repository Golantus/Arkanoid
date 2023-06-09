#pragma once
#include "BuffListEnum.h"
#include "MoveableActor.h"

class Platform : public MoveableActor
{

public:
	void reset(point startCoordinates);
	int movePlatform(double tickTime, bool goToRight);
	void buffUpdate(double tickTime);

	bool isReadyToCatchBall();
	void setReadyToCatchBall(bool ready);
	bool canShootProjectile();
	void applyBuff(BuffType type, double duration);

	Platform(SDL_Texture* texturePointer);

	~Platform();

private:
	bool readyToCatchBall;

	int initialWidth;

	double buffTimer[3];
	bool buffApplied[3];

	void buffReset();
};

