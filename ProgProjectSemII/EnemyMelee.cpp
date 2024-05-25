// Name: Pavel Dobias
// Login: C00301332

#include "EnemyMelee.h"


EnemyMelee::EnemyMelee()
{
	setupEnemy();	// set the enemy sprite and texture
	setPosition();	// set the position of the enemy

	speed = 1; // the average speed
	health = 1000;
}

void EnemyMelee::setupEnemy()
{
	if (!textureNorth.loadFromFile("ASSETS\\TEXTURES\\enemy2_up.png"))
	{
		std::cout << "problem loading enemy facing up" << std::endl;
	}

	if (!textureSouth.loadFromFile("ASSETS\\TEXTURES\\enemy2_down.png"))
	{
		std::cout << "problem loading enemy facing down" << std::endl;
	}

	if (!textureWest.loadFromFile("ASSETS\\TEXTURES\\enemy2_left.png"))
	{
		std::cout << "problem loading enemy facing left" << std::endl;
	}

	if (!textureEast.loadFromFile("ASSETS\\TEXTURES\\enemy2_right.png"))
	{
		std::cout << "problem loading enemy facing right" << std::endl;
	}

	enemySprite.setTexture(textureSouth);	// sets the player sprite
}

sf::Sprite EnemyMelee::getBody()
{
	return sf::Sprite(enemySprite);	
}

void EnemyMelee::setPosition()
{
	enemySprite.setPosition(m_enemyPos.x, m_enemyPos.y);
}

void EnemyMelee::setPosition(float xPos, float yPos)
{
	enemySprite.setPosition(xPos, yPos);
}

sf::Vector2f EnemyMelee::getPosition()
{
	sf::Vector2f pos(enemySprite.getPosition());	// gets the current position of the enemy
	return pos;	// returns that pos
}

void EnemyMelee::enemyMovement(float xPos, float yPos)	// gets the player xPos and yPos
{
	sf::Vector2f enemyPos = enemySprite.getPosition();	// gets the position of the enemy sprite
	sf::Vector2f direction;	// variables for the enemy movement
	float length;
	sf::Vector2f velocity;
	
	direction = sf::Vector2f(xPos, yPos) - enemyPos;	// the direction is player pos minus enemy ppos

	length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // pythagoros equation for the lenght

	velocity.x = (direction.x / length);	// velocity is direction divided by lenght multiplied by the enemy speed
	velocity.y = (direction.y / length);
	velocity.x = velocity.x * speed;
	velocity.y = velocity.y * speed;

	enemySprite.setPosition(enemyPos.x + velocity.x, enemyPos.y + velocity.y);	// we set the enemy positon with added velocity
}

void EnemyMelee::checkBoundaries()	// the boundaries for this enemy are not neccesary but left in here just in case
{
	sf::Vector2f pos(enemySprite.getPosition());	// get pos of enemy
	if (pos.x > SCREEN_WIDTH)	// if the x pos of the enemy is more then screen width minus size of the enemy sprite
	{
		enemySprite.setPosition(SCREEN_WIDTH, pos.y);	// set the pos of the player to that location = player cannot cross the boundary
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

int EnemyMelee::checkDirection()
{
	return 0;
}

bool EnemyMelee::checkAlive()
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

void EnemyMelee::dealDamage(int damage)
{
	if (health > 0)
	{
		health = health - damage;	
	}
	else
	{
		isAlive = false;
		setPosition(2000.0f, 2000.0f);	// set the enemy out of screen boundary
	}
}

void EnemyMelee::respawn()
{
	isAlive = true;	// enemy is alive again
}
