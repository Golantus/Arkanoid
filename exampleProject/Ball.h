#pragma once
#include "MoveableActor.h"	
#include <memory>


class Ball : public MoveableActor
{
public:
	Ball(SDL_Rect platformRect, SDL_Texture* tex);
	Ball(const std::unique_ptr<Ball>& mainBall, SDL_Texture* tex);

	void moveWithPlatform(int dX);
	void launchBall(point mouseCoords);

	bool getIsLost();
	bool isStickToPlatform();
	void setStickToPlatform(bool stick);

	bool checkBallCollisionWithBlock(Actor& block);
	bool checkBallCollisionWithPlatform(Actor& platform);
	bool checkBallCollisionWithScreenBorders();
private:
	bool stickToPlatform;
	bool isLost;
	point startCoordinates;
	double initialSpeed;


};

