#pragma once
#include "Actor.h"

class MoveableActor : public Actor
{
public:
	MoveableActor();
	MoveableActor(SDL_Rect textureRect, SDL_Texture* texturePointer);
	void move(double tickTime);
	void setSpeed(double speed);
	void setMovementVector(vector2D vec);

	vector2D getMovementVector() const;
	double getSpeed() const;
private:
	point temporaryCoordinates;
	vector2D movementVector;
	double currentSpeed;
};