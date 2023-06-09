#include "Ball.h"
#include "Platform.h"
#include "RNGFunc.h"
#include "Brick.h"

#define BALL_MAX_SPEED initialSpeed * 1.7
#define BALL_MIN_SPEED initialSpeed * 0.9
#define BALL_SPEED_INCREASE 1.1
#define BALL_SPEED_DECREASE 0.9

Ball::Ball(SDL_Rect platformRect, SDL_Texture* tex)
	:MoveableActor( SDL_Rect{(platformRect.x + platformRect.w / 2 - 16), (platformRect.y - 30),25, 25 }, tex),
	 initialSpeed(500),
	 isLost(0), stickToPlatform(1)
{
	setSpeed(5);
}

Ball::Ball(const std::unique_ptr<Ball>& mainBall, SDL_Texture* tex)
	:MoveableActor(mainBall->getHitbox(), tex),
	isLost(0), stickToPlatform(0)
{
	vector2D newMoveVec;
	if (!mainBall->isStickToPlatform())
	{
		SDL_Rect newHitbox = getHitbox();
		newHitbox.y -= 2;
		setHitbox(newHitbox);
		initialSpeed = mainBall->getSpeed();
		newMoveVec.y = getRandomNumber(1, 100);
		newMoveVec.y *= -1;
	}
	else
	{
		initialSpeed = 500;
		do {
			newMoveVec.y = getRandomNumber(-100, 100);
		} while (newMoveVec.y == 0);
	}

	do {
		newMoveVec.x = getRandomNumber(-100, 100);
	} while (newMoveVec.x == 0);

	setMovementVector(newMoveVec);
	setSpeed(initialSpeed);
}

bool Ball::checkBallCollisionWithBlock(Actor& block)
{
	bool collided = false;

	Brick* blockIsBrick = dynamic_cast<Brick*>(&block);
	if (blockIsBrick) {
		if (blockIsBrick->getDestroyed())
			return collided;
	}

	if (checkCollisionsWithOtherActor(block))
	{
		if (blockIsBrick) {
			blockIsBrick->brickGetHit();
			if (blockIsBrick->getDestroyed())
			{
				setSpeed(getSpeed() * BALL_SPEED_DECREASE);
				if (getSpeed() < BALL_MIN_SPEED)
					setSpeed(BALL_MIN_SPEED);
			}
		}

		int DELTA_X = 0, DELTA_Y = 0; //detecting direction to reflect the ball

		//rectangle 1 is ball, rectangle 2 is brick (or platform)
		vector2D newMovementVector = getMovementVector();

		if (newMovementVector.x > 0)
			DELTA_X = (this->getRightBorder()) - block.getLeftBorder();
		else if (newMovementVector.x < 0)
			DELTA_X = (block.getRightBorder()) - this->getLeftBorder();

		if (newMovementVector.y > 0)
			DELTA_Y = (this->getLowerBorder()) - block.getUpperBorder();
		else if (newMovementVector.y < 0)
			DELTA_Y = (block.getLowerBorder()) - this->getUpperBorder();

		bool xCollision = false;
		bool yCollision = false;
		if (DELTA_X == DELTA_Y) 
		{
			xCollision = true;
			yCollision = true;
		}
		else if (DELTA_X > DELTA_Y) 
		{
			yCollision = true;
		}
		else if (DELTA_X < DELTA_Y) 
		{
			xCollision = true;
		}
		if (xCollision)
		{
			if (newMovementVector.x > 0)
				this->setXCoordinate(block.getLeftBorder() - this->getWidth());
			else
				this->setXCoordinate(block.getRightBorder());
			newMovementVector.x *= -1;
			collided = true;
		}
		if (yCollision)
		{
			if (newMovementVector.y > 0)
				this->setYCoordinate(block.getUpperBorder() - this->getHeight());
			else
				this->setYCoordinate(block.getLowerBorder());
			newMovementVector.y *= -1;
			collided = true;
		}
		setMovementVector(newMovementVector);
	}
	return collided;
}

bool Ball::checkBallCollisionWithPlatform(Actor& platform)
{
	bool collided = checkBallCollisionWithBlock(platform);
	if (collided) {
		setSpeed(getSpeed() * BALL_SPEED_INCREASE);
		if (getSpeed() > BALL_MAX_SPEED)
			setSpeed(BALL_MAX_SPEED);

		if (dynamic_cast<Platform*>(&platform)->isReadyToCatchBall())
		{
			vector2D movVec = getMovementVector();
			if (getMovementVector().y > 0)
				movVec.y *= -1;
			setMovementVector(movVec);

			setYCoordinate(platform.getUpperBorder() - this->getHeight());
			if (getRightBorder() > platform.getHitboxCenter().x + (platform.getWidth() - 10))
				setXCoordinate(getLeftBorder() - 20);
			else if (getLeftBorder() < platform.getHitboxCenter().x - (platform.getWidth() - 10))
				setXCoordinate(getLeftBorder() + 20);
		}
	}
	return collided;
}

bool Ball::checkBallCollisionWithScreenBorders()
{
	vector2D newMovementVector = getMovementVector();

	bool collided = 0;
	if (getLeftBorder() <= 0) {
		setXCoordinate(0 + 1);
		newMovementVector.x *= -1;
		collided = 1;
	}
	else if (getRightBorder() >= LOGIC_SCREEN_WIDTH) {
		setXCoordinate(LOGIC_SCREEN_WIDTH - getWidth() - 1);
		newMovementVector.x *= -1;
		collided = 1;
	}
	if (getUpperBorder() <= 0) {
		setYCoordinate(0 + 1);
		newMovementVector.y *= -1;
		collided = 1;
	}
	else if (getUpperBorder() >= LOGIC_SCREEN_HEIGHT) {
		isLost = 1;
		collided = 1;
	}

	if (collided)
	{
		setSpeed(getSpeed() * BALL_SPEED_INCREASE);
		if (getSpeed() > BALL_MAX_SPEED)
			setSpeed(BALL_MAX_SPEED);
	}

	setMovementVector(newMovementVector);
	return collided;
}

void Ball::moveWithPlatform(int dX)
{
	setXCoordinate(getLeftBorder() + dX);
}

void Ball::launchBall(point mouseCoords)
{
	vector2D movVec(mouseCoords.x - getLeftBorder(), mouseCoords.y - getUpperBorder());

	if (movVec.y >= 0)
		return;
	if (movVec.x == 0)
		movVec.x = 1;
	setSpeed(initialSpeed);
	setStickToPlatform(0);
	setMovementVector(movVec);
}

bool Ball::getIsLost()
{
	return isLost;
}

bool Ball::isStickToPlatform()
{
	return stickToPlatform;
}

void Ball::setStickToPlatform(bool stick)
{
	stickToPlatform = stick;
}
