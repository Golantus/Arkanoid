#include <fstream>
#include <iostream>
#include "Level.h"
#include "RNGFunc.h"

#define LEVEL_TEX_LIST
#include "TextureList.h"

extern SDL_Renderer* rend;


Level::Level(LevelNumberEnum num)
	:currentLevelNumber(num), hasWon(0),
	holdingButtonA(0), holdingButtonD(0),
	timerToShootProjectile(0),
	platform(new Platform(platformTexture)),
	extraHealthSymbol({0,0,0,0}, heartSymbolTexture)
{
	loadLevelMapFromFile();
	extraHealth = initialHealth;
	ballList.push_back(std::make_unique<Ball>(Ball(platform->getHitbox(), ballTexture)));
	
	updateRedBricks();
}


int Level::tick(double tickTime, const std::list<myEventTypes>& events)
{
	if (ballList.empty())
	{
		if (extraHealth > 0)
		{
			extraHealth--;
			ballList.push_back(std::make_unique<Ball>(Ball(platform->getHitbox(), ballTexture)));
		}
		else
			return -1;
	}
	if (hasWon)
		return 1;

	eventManagement(events);
	int platformMovement = 0;
	moveActors(tickTime, platformMovement);

	ballCollisionAndMovementManagement(tickTime, platformMovement);
	checkBuffCollision();
	checkProjectileCollision();
	platform->buffUpdate(tickTime);
	if (platform->canShootProjectile())
	{
		timerToShootProjectile += tickTime;
		if (timerToShootProjectile >= 0.24)
		{
			timerToShootProjectile -= 0.24;
			shootProjectile(platform->getHitboxCenter());
		}
	}
	else
		timerToShootProjectile = 0;

	renderActors();
	return 0;
}

void Level::ballCollisionAndMovementManagement(double tickTime, int platformMovement)
{
	std::list<std::unique_ptr<Ball>*> deleteBallList;
	for (auto& ball : ballList)
	{
		if (ball->isStickToPlatform())
		{
			ball->moveWithPlatform(platformMovement);
			continue;
		}

		int collisionSplit = 4;

		for (int i = 0; i < collisionSplit; i++)
		{
			ball->move(tickTime / collisionSplit);
			if (checkBallCollisions(ball))
			{
				if (ball->getIsLost())
				{
					deleteBallList.emplace_back(&ball);
					break;
				}
				updateRedBricks();
				break;
			}
		}
	}
	for (auto& ball : deleteBallList)
	{
		ballList.remove(*ball);
	}
}

void Level::shootProjectile(point platformHitboxCenter)
{
	SDL_Rect projectileRect{(int)platformHitboxCenter.x, (int)platformHitboxCenter.y, 8, 15};
	projectileList.push_back(std::make_unique<MoveableActor>(MoveableActor(projectileRect, platformTexture)));
	projectileList.back()->setMovementVector(point(0,-10));
	projectileList.back()->setSpeed(30);
}

bool Level::checkBallCollisions(const std::unique_ptr<Ball>& ball)
{
	if (ball->checkBallCollisionWithScreenBorders()) //screen borders collision
		return true;

	for (const auto& brick : brickList) //brick collision
	{
		if (ball->checkBallCollisionWithBlock(*brick))
		{
			if (brick->getDestroyed())
				if (getRandomNumber(1, 100) <= chanceToSpawnBuff)
					spawnBuff(brick->getHitbox());
			return true;
		}
	}

	if (ball->checkBallCollisionWithPlatform(*platform)) // platform collision
	{
		if (readyToWin())
		{
			hasWon = 1;
		}
		else if (platform->isReadyToCatchBall())
		{
			ball->setSpeed(platform->getSpeed());
			ball->setStickToPlatform(1);
		}
		return true;
	}
	return false;
}

void Level::spawnBuff(SDL_Rect brickHitbox)
{
	int randomNumber;
	BuffType buff;
	do
	{
		randomNumber = getRandomNumber(0, 5);
		buff = static_cast<BuffType>(randomNumber+BUFF_TYPE_ENUM_START);
	} while (buff == EXTRA_LIFE_BUFF && extraHealth == 5);

	buffList.push_back(std::make_unique<Buff>(Buff(brickHitbox, buff)));
}

void Level::tryToLaunchBall(point mouseCoords)
{
	for (auto& ball : ballList)
	{
		if (ball->isStickToPlatform())
			ball->launchBall(mouseCoords);
	}
}

void Level::renderActors()
{
	SDL_RenderClear(rend);

	levelBackground.draw();

	for (const auto& brick : brickList)
	{
		if(!brick->getDestroyed())
			brick->draw();
	}

	for (const auto& ball : ballList)
	{
		ball->draw();
	}

	for (const auto& projectile : projectileList)
	{
		projectile->draw();
	}

	platform->draw();

	for (const auto& buff : buffList)
	{
		buff->draw();
	}

	SDL_Rect heartRect = { -45, 0 , 40 , 40 };
	for (int i = 0; i < extraHealth; i++)
	{

		heartRect.x += heartRect.w + 10;
		extraHealthSymbol.setHitbox(heartRect);
		extraHealthSymbol.draw();
	}

	SDL_RenderPresent(rend);
}

LevelNumberEnum Level::getLevelNumber()
{
	return currentLevelNumber;
}

void Level::checkBuffCollision()
{
	std::list<std::unique_ptr<Buff>*> deleteBuffList;

	for (auto& buff : buffList)
	{
		if (platform->checkCollisionsWithOtherActor(*buff))
		{
			if (buff->isApplyingToPlatform())
				platform->applyBuff(buff->getType(), buff->getDuration());
			else
			{
				BuffType type = buff->getType();
				int numOfBalls = 1;
				switch (type)
				{
				case BONUS_BALL_BUFF:
					if (getRandomNumber(0, 100) > 80)
						numOfBalls = 2;
					for (int i = 0; i < numOfBalls; i++)
						ballList.push_back(std::make_unique<Ball>(Ball(ballList.back(), ballTexture)));
					break;
				case EXTRA_LIFE_BUFF:
					if (extraHealth < 5)
						extraHealth++;
					break;
				}
			}
			deleteBuffList.emplace_back(&buff);
		}
	}
	for (auto& buff : deleteBuffList)
		buffList.remove(*buff);
}

void Level::checkProjectileCollision()
{
	std::list<std::unique_ptr<MoveableActor>*> deleteProjectileList;
	for (auto& projectile : projectileList)
	{
		for (const auto& brick : brickList)
		{
			if (!brick->getDestroyed())
			{
				if (projectile->checkCollisionsWithOtherActor(*brick))
				{
					brick->destroyBrick();
					deleteProjectileList.emplace_back(&projectile);
				}
			}
		}
	}

	for (auto& projectile : deleteProjectileList)
		projectileList.remove(*projectile);
}

void Level::updateRedBricks()
{
	for (auto& brick : brickList)
	{
		if (brick->getDestroyed())
			continue;
		if (brick->getType() != RED_BRICK && brick->getType() != GRAY_BRICK)
			return;
	}
	for (auto& brick : brickList)
		brick->setCanBeBroken();
}

bool Level::readyToWin()
{
	bool readyToWin = 1;
	for (auto& brick : brickList)
	{
		if (brick->getDestroyed())
			continue;
		if (brick->getType() != GRAY_BRICK)
		{
			readyToWin = 0;
			break;
		}
	}
	return readyToWin;
}

void Level::moveActors(double tickTime, int &platformMovement)
{
	for (auto& buff: buffList)
	{
		buff->move(tickTime);
	}
	for (auto& projectile : projectileList)
	{
		projectile->move(tickTime);
	}
	if (holdingButtonA && !holdingButtonD)
	{
		platformMovement = platform->movePlatform(tickTime, 0);
	}
	else if (!holdingButtonA && holdingButtonD)
	{
		platformMovement = platform->movePlatform(tickTime, 1);
	}
}

void Level::loadLevelMapFromFile()
{
	std::string path;
	SDL_Rect mapBackgroundSize = {0, 0, 1600, 900};
	switch (currentLevelNumber)
	{
	case LEVEL1:
		path = "levels/level1.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture1);
		chanceToSpawnBuff = 50;
		initialHealth = 3;
		break;
	case LEVEL2:
		path = "levels/level2.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture1);
		chanceToSpawnBuff = 50;
		initialHealth = 3;
		break;
	case LEVEL3:
		path = "levels/level3.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture1);
		chanceToSpawnBuff = 35;
		initialHealth = 3;
		break;
	case LEVEL4:
		path = "levels/level4.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture2);
		chanceToSpawnBuff = 35;
		initialHealth = 3;
		break;
	case LEVEL5:
		path = "levels/level5.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture2);
		chanceToSpawnBuff = 25;
		initialHealth = 3;
		break;
	case LEVEL6:
		path = "levels/level6.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture2);
		chanceToSpawnBuff = 25;
		initialHealth = 3;
		break;
	case LEVEL7:
		path = "levels/level7.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture3);
		chanceToSpawnBuff = 25;
		initialHealth = 2;
		break;
	case LEVEL8:
		path = "levels/level8.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture3);
		chanceToSpawnBuff = 20;
		initialHealth = 2;
		break;
	case LEVEL9:
		path = "levels/level9.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture3);
		chanceToSpawnBuff = 34;
		initialHealth = 2;
		break;
	case LEVEL10:
		path = "levels/level10.txt";
		levelBackground = Actor(mapBackgroundSize, levelBackgroundTexture1);
		chanceToSpawnBuff = 20;
		initialHealth = 1;
		break;
	default:
		break;
	}

	std::ifstream file(path);
	
	if (!file)
	{
		std::cout<< "file " << path << " is missing";
		return;
	}

	
	const int MAX_ROW = 24;
	const int MAX_COL = 32;
	int row = 0;
	while (file) //max size is locked to 32x24 rectangle
	{ 
		std::string currentRowString;
		file >> currentRowString;
		currentRowString.resize(MAX_COL);
		for (size_t column = 0; column < currentRowString.length(); column++)
		{
			SDL_Rect brickRect = { column * 50, row * 25, 50, 25 };

			switch (currentRowString[column])
			{
			case ('0'):
				brickList.push_back(std::make_unique<Brick>(Brick(brickRect, BLUE_BRICK)));
				break;
			case ('1'):
				brickList.push_back(std::make_unique<Brick>(Brick(brickRect, RED_BRICK)));
				break;
			case ('2'):
				brickList.push_back(std::make_unique<Brick>(Brick(brickRect, YELLOW_BRICK)));
				break;
			case ('3'):
				brickList.push_back(std::make_unique<Brick>(Brick(brickRect, GRAY_BRICK)));
				break;
			default:
				break;
			}
		}
		row++;
		if (row == MAX_ROW)
			break;
	}
}

void Level::eventManagement(const std::list<myEventTypes>& events)
{
	for (auto event : events)
	{
		switch (event)
		{
		case PRESSED_A:
			holdingButtonA = 1;
			break;
		case PRESSED_D:
			holdingButtonD = 1;
			break;
		case RELEASED_A:
			holdingButtonA = 0;
			break;
		case RELEASED_D:
			holdingButtonD = 0;
			break;
		case RELEASED_BOTH:
			holdingButtonA = 0;
			holdingButtonD = 0;
			break;
		case PRESSED_BOTH:
			holdingButtonA = 1;
			holdingButtonD = 1;
		default:
			break;
		}
	}
}

void Level::restart()
{
	hasWon = 0;
	holdingButtonA = 0;
	holdingButtonD = 0;
	extraHealth = initialHealth;
	platform.reset(new Platform(platformTexture));
	for (auto& brick : brickList)
	{
		brick->reset();
	}
	ballList.clear();
	buffList.clear();
	projectileList.clear();
	ballList.push_back(std::make_unique<Ball>(Ball(platform->getHitbox(), ballTexture)));
}
