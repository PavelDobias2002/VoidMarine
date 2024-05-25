// Name: Pavel Dobias
// Login: C00301332

#include "EnemyRanged.h"
#include <random>  // for randomazing

EnemyRanged::EnemyRanged()
{
	setupEnemy();	// set the enemy sprite and texture
	setPosition();	// set the position of the enemy

	speed = 4; // the average speed
	health = 100;
}

void EnemyRanged::setupEnemy()
{
	if (!textureNorth.loadFromFile("ASSETS\\TEXTURES\\enemy1_up.png"))
	{
		std::cout << "problem loading enemy facing up" << std::endl;
	}

	if (!textureSouth.loadFromFile("ASSETS\\TEXTURES\\enemy1_down.png"))
	{
		std::cout << "problem loading enemy facing down" << std::endl;
	}

	if (!textureWest.loadFromFile("ASSETS\\TEXTURES\\enemy1_left.png"))
	{
		std::cout << "problem loading enemy facing left" << std::endl;
	}

	if (!textureEast.loadFromFile("ASSETS\\TEXTURES\\enemy1_right.png"))
	{
		std::cout << "problem loading enemy facing right" << std::endl;
	}

	enemySprite.setTexture(textureSouth);	// sets the player sprite
}

sf::Sprite EnemyRanged::getBody()
{
	return sf::Sprite(enemySprite);
}

void EnemyRanged::setPosition()
{
	enemySprite.setPosition(m_enemyPos.x, m_enemyPos.y);
}

void EnemyRanged::setPosition(float xPos, float yPos)
{
	enemySprite.setPosition(xPos, yPos);
}

sf::Vector2f EnemyRanged::getPosition()
{
	sf::Vector2f pos(enemySprite.getPosition());	// gets the current position of the enemy
	return pos;	// returns that pos
}

void EnemyRanged::enemyMovement()	// gets the player xPos and yPos
{
	sf::Vector2f pos(enemySprite.getPosition());	// get pos of the enemy sprite
	if (direction == 1)
	{
		enemySprite.setPosition(pos.x, pos.y + speed);
		enemySprite.setTexture(textureSouth);
	}
	else if (direction == 2)
	{
		enemySprite.setPosition(pos.x, pos.y - speed);
		enemySprite.setTexture(textureNorth);
	}
	else if (direction == 3)
	{
		enemySprite.setPosition(pos.x + speed, pos.y);
		enemySprite.setTexture(textureEast);
	}
	else if (direction == 4)
	{
		enemySprite.setPosition(pos.x - speed, pos.y);
		enemySprite.setTexture(textureWest);
	}
	
}

void EnemyRanged::checkBoundaries()	// the boundaries for this enemy are not neccesary but left in here just in case
{
	sf::Vector2f pos(enemySprite.getPosition());	// get pos of player
	if (pos.x > SCREEN_WIDTH - 64.0f)	// if the x pos of the player is more then screen width minus size of the player sprite
	{
		enemySprite.setPosition(SCREEN_WIDTH - 64.0f, pos.y);	// set the pos of the player to that location = player cannot cross the boundary
	}
	else if (pos.x < 0.0f)	// same but if the pos is less then 0, left edge of the screen
	{
		enemySprite.setPosition(0.0f, pos.y);	// set the pos of player to 0 = cannot cross the boundary
	}

	if (pos.y > SCREEN_HEIGHT - 64.0f)
	{
		enemySprite.setPosition(pos.x, SCREEN_HEIGHT - 64.0f);
	}
	else if (pos.y < 0.0f)
	{
		enemySprite.setPosition(pos.x, 0.0f);
	}
}

int EnemyRanged::checkDirection()
{
	return 0;
}

bool EnemyRanged::checkAlive()
{
	if (isAlive == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void EnemyRanged::dealDamage(int damage)
{
	if (health > 0)	// if the health is 
	{
		health = health - damage;
	}
	else
	{
		isAlive = false;	// if not enemy dies and is teleported out of the screen
		
		setPosition(2000.0f, 2000.0f);
	}
}

void EnemyRanged::changeDirection(int randomDirection)
{
	direction = randomDirection;
	isMoving = true;
}

bool EnemyRanged::checkMoving()
{
	if (isMoving == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void EnemyRanged::respawn()
{
	isAlive = true;
}
