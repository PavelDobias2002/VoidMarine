// Name: Pavel Dobias
// Login: C00301332

#include "Bullet.h"

Bullet::Bullet()
{
	
	setupBullet();	// function to setup sprite texture etc.
	setPosition();

	speed = 2;
}

void Bullet::setupBullet()
{
	// loads all the textures for the enemy bullet
	if (!textureNorth.loadFromFile("ASSETS\\TEXTURES\\fireball_up.png"))
	{
		std::cout << "problem loading firing up" << std::endl;
	}

	if (!textureSouth.loadFromFile("ASSETS\\TEXTURES\\fireball_down.png"))
	{
		std::cout << "problem loading firing down" << std::endl;
	}

	if (!textureWest.loadFromFile("ASSETS\\TEXTURES\\fireball_left.png"))
	{
		std::cout << "problem loading firing left" << std::endl;
	}

	if (!textureEast.loadFromFile("ASSETS\\TEXTURES\\fireball_right.png"))
	{
		std::cout << "problem loading firing right" << std::endl;
	}

}

sf::Sprite Bullet::getBody()
{
	return sf::Sprite(bulletSprite);	// returns the bullet sprite
}

void Bullet::setPosition()
{

}

void Bullet::setPosition(float xPos, float yPos)
{
	bulletSprite.setPosition(xPos, yPos);
}

sf::Vector2f Bullet::getPosition()
{
	sf::Vector2f pos(bulletSprite.getPosition());
	return pos;
}

void Bullet::beingFired(float  xPos, float yPos, int m_direction)
{
	isFiring = true;	// firing is set to true
	bulletSprite.setPosition(xPos, yPos);	// position of the bullet is set to the player position or enemy position
	direction = m_direction;
}

void Bullet::bulletMovement()	
{
	if (isFiring == true)	// when the bullet is being fired
	{
		if (direction == NORTH)	// based on the direction player was facing the proper texture is loaded
		{
			sf::Vector2f pos(bulletSprite.getPosition());	//get position of the bullet sprite
			bulletSprite.setPosition(pos.x, pos.y - speed);	// movement of the bullet
			bulletSprite.setTexture(textureNorth);
		}
		if (direction == SOUTH)
		{
			sf::Vector2f pos(bulletSprite.getPosition());	//get position of the bullet sprite
			bulletSprite.setPosition(pos.x, pos.y + speed);
			bulletSprite.setTexture(textureSouth);
		}
		if (direction == WEST)
		{
			sf::Vector2f pos(bulletSprite.getPosition());	//get position of the bullet sprite
			bulletSprite.setPosition(pos.x - speed, pos.y);
			bulletSprite.setTexture(textureWest);
		}
		if (direction == EAST)
		{
			sf::Vector2f pos(bulletSprite.getPosition());	//get position of the bullet sprite
			bulletSprite.setPosition(pos.x + speed, pos.y);
			bulletSprite.setTexture(textureEast);
		}
	}

	
}


void Bullet::checkBoundaries()
{
	sf::Vector2f pos(bulletSprite.getPosition());	// get pos of bullet sprite
	if (pos.x > SCREEN_WIDTH - 64.0f)	// if the bullets position is at the boundary of the screen set the isFiring to false, player can fire again
	{
		isFiring = false;
	}
	else if (pos.x < 0.0f)	// same for all the edges of the screen
	{
		isFiring = false;
	}

	if (pos.y > SCREEN_HEIGHT - 64.0f)
	{
		isFiring = false;
	}
	else if (pos.y < 0.0f)
	{
		isFiring = false;
	}
}

bool Bullet::checkFiring()
{
	if (isFiring == false)	// just returns if firing is true or not
	{
		return false;
	}
	else
	{
		return true;
	}
}



