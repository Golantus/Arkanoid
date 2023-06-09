#pragma once
#include "Ball.h"
#include "Platform.h"
#include "Buff.h"
#include "Brick.h"
#include <list>

enum myEventTypes
{
	PRESSED_A,
	PRESSED_D,
	RELEASED_A,
	RELEASED_D,
	PRESSED_LEFT_ARROW = PRESSED_A,
	PRESSED_RIGHT_ARROW = PRESSED_D,
	RELEASED_LEFT_ARROW = RELEASED_A,
	RELEASED_RIGHT_ARROW = RELEASED_D,
	PRESSED_BOTH,
	RELEASED_BOTH,
	EVENTS_END
};

enum LevelNumberEnum
{
	LEVEL1 = 1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,
	LEVEL8,
	LEVEL9,
	LEVEL10
};

class Level
{
public:
	Level(LevelNumberEnum);

	LevelNumberEnum currentLevelNumber;

	int tick(double tickTime, const std::list<myEventTypes>& events);
	void tryToLaunchBall(point mouseCoords);
	void restart();
	LevelNumberEnum getLevelNumber();
private:

	void checkBuffCollision();
	void checkProjectileCollision();
	void updateRedBricks();
	bool readyToWin();
	void moveActors(double tickTime, int &platformMovement);
	void renderActors();
	void loadLevelMapFromFile();
	void eventManagement(const std::list<myEventTypes>& events);
	void ballCollisionAndMovementManagement(double tickTime, int platformMovement);
	void shootProjectile(point platformHitboxCenter);
	bool checkBallCollisions(const std::unique_ptr<Ball>& ball);
	void spawnBuff(SDL_Rect brickHitbox);

	bool holdingButtonA;
	bool holdingButtonD;
	bool hasWon;
	int chanceToSpawnBuff;
	int extraHealth;
	int initialHealth;
	double timerToShootProjectile;

	SDL_Rect platformRect;
	Actor levelBackground;
	Actor extraHealthSymbol;
	std::unique_ptr<Platform> platform;
	std::list<std::unique_ptr<Ball>> ballList;
	std::list<std::unique_ptr<MoveableActor>> projectileList;
	std::list<std::unique_ptr<Brick>> brickList;
	std::list<std::unique_ptr<Buff>> buffList;
};
