#include "MoveableActor.h"

MoveableActor::MoveableActor()
	:Actor()
{
}

MoveableActor::MoveableActor(SDL_Rect textureRect, SDL_Texture* texturePointer)
	:Actor(textureRect, texturePointer)
{
	
}

void MoveableActor::move(double tickTime)
{
	double relativeSpeed = currentSpeed;

	if(movementVector.x != 0 && movementVector.y != 0)
		relativeSpeed = (currentSpeed  / sqrt((movementVector.x * movementVector.x) + (movementVector.y * movementVector.y)));


	if (movementVector.x != 0) {
		temporaryCoordinates.x += movementVector.x * relativeSpeed * tickTime;
		if (temporaryCoordinates.x >= 1.0 || temporaryCoordinates.x <= -1.0) {
			int newXCoord = getLeftBorder() + int(temporaryCoordinates.x);
			setXCoordinate(newXCoord);
			temporaryCoordinates.x -= int(temporaryCoordinates.x);
		}
	}

	if (movementVector.y != 0) {
		temporaryCoordinates.y += movementVector.y * relativeSpeed * tickTime;
		if (temporaryCoordinates.y >= 1.0 || temporaryCoordinates.y <= -1.0) {
			int newYCoord = getUpperBorder() + int(temporaryCoordinates.y);
			setYCoordinate(newYCoord);
			temporaryCoordinates.y -= int(temporaryCoordinates.y);
		}
	}
}

void MoveableActor::setSpeed(double speed)
{
	currentSpeed = speed;
}

void MoveableActor::setMovementVector(vector2D vec)
{
	movementVector = vec;
}

vector2D MoveableActor::getMovementVector() const
{
	return movementVector;
}

double MoveableActor::getSpeed() const
{
	return currentSpeed;
}
