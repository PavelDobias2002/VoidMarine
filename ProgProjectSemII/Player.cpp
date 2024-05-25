// Name: Pavel Dobias
// Login: C00301332

#include "Player.h"   // include Player header file

// Player function definitions here
Player::Player()
{
	setupPlayer();
	setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);	// sets player in the middle of the screen

	speed = 5; // the average speed
	health = 200;
}

void Player::setupPlayer()
{
	// load all the textures for the player facings
		if (!textureNorth.loadFromFile("ASSETS\\TEXTURES\\player_up.png"))
		{
			std::cout << "problem loading facing up" << std::endl;
		}
		
		if (!textureSouth.loadFromFile("ASSETS\\TEXTURES\\player_down.png"))
		{
			std::cout << "problem loading facing down" << std::endl;
		}
	
		if (!textureWest.loadFromFile("ASSETS\\TEXTURES\\player_left.png"))
		{
			std::cout << "problem loading facing left" << std::endl;
		}

		if (!textureEast.loadFromFile("ASSETS\\TEXTURES\\player_right.png"))
		{
			std::cout << "problem loading facing right" << std::endl;
		}

		if (!idleTexture.loadFromFile("ASSETS\\TEXTURES\\idle_stand.png"))
		{
			std::cout << "problem loading idle state" << std::endl;
		}

		if (!deadTexture.loadFromFile("ASSETS\\TEXTURES\\dead_player.png"))
		{
			std::cout << "problem loading dead state" << std::endl;
		}

		playerSprite.setTexture(idleTexture);	// sets the player sprite in idle
}

sf::Sprite Player::getBody()
{
	return sf::Sprite(playerSprite);	// return sprite of the player
}

void Player::setPosition()	// sets position of the player on the screen
{
	playerSprite.setPosition(300, 200);
}

void Player::setPosition(int xPos, int yPos)	// sets position of the player on the screen
{
	playerSprite.setPosition(xPos, yPos);
}

sf::Vector2f Player::getPosition()
{
	sf::Vector2f pos(playerSprite.getPosition());	// gets the current pos of player
	return pos;	
}

void Player::playerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	// if A or LEFT is pressed
	{
		direction = WEST;	// change the direction to the West
		sf::Vector2f pos(playerSprite.getPosition());	// get position of the sprite
		playerSprite.setPosition(pos.x - speed, pos.y);	// change that position based on the direction
		playerSprite.setTexture(textureWest);	// change sprite to texture based on direction
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	// do the same for D, W and S and UP, DOWN, LEFT and RIGHT
	{
		direction = EAST;
		sf::Vector2f pos(playerSprite.getPosition());
		playerSprite.setPosition(pos.x + speed, pos.y);
		playerSprite.setTexture(textureEast);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = NORTH;
		sf::Vector2f pos(playerSprite.getPosition());
		playerSprite.setPosition(pos.x, pos.y - speed);
		playerSprite.setTexture(textureNorth);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = SOUTH;
		sf::Vector2f pos(playerSprite.getPosition());
		playerSprite.setPosition(pos.x, pos.y + speed);
		playerSprite.setTexture(textureSouth);
	}
		
}

void Player::stopMovement()
{
	sf::Vector2f pos(playerSprite.getPosition());	// gets current pos of sprite
	playerSprite.setPosition(pos.x, pos.y);			// makes it to stop
}

void Player::checkBoundaries()
{
	sf::Vector2f pos(playerSprite.getPosition());	// get pos of player
	if (pos.x > SCREEN_WIDTH - 50.0f)	// if the x pos of the player is more then screen width minus size of the player sprite
	{
		playerSprite.setPosition(SCREEN_WIDTH - 64.0f, pos.y);	// set the pos of the player to that location = player cannot cross the boundary
	}
	else if (pos.x < 0.0f)	// same but if the pos is less then 0, left edge of the screen
	{
		playerSprite.setPosition(0.0f, pos.y);	// set the pos of player to 0 = cannot cross the boundary
	}

	if (pos.y > SCREEN_HEIGHT - 50.0f)
	{
		playerSprite.setPosition(pos.x, SCREEN_HEIGHT - 64.0f);
	}
	else if (pos.y < 0.0f)
	{
		playerSprite.setPosition(pos.x, 0.0f);
	}
}

int Player::checkDirection()	// return current direction
{
	if (direction == NORTH)
	{
		return NORTH;
	}
	else if (direction == SOUTH)
	{
		return SOUTH;
	}
	else if (direction == WEST)
	{
		return WEST;
	}
	else if (direction == EAST)
	{
		return EAST;
	}
}

void Player::decreaseHealth(int damage)
{
	if (health > 0)
	{
		health = health - damage;
	}
	else
	{
		isAlive = false;
		playerSprite.setTexture(deadTexture);	// if player is dead set the texture to dead player
	}
}

bool Player::checkAlive()
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

int Player::checkHealth()
{
	return health;
}

void Player::resetLives()
{
	health = 200; // sets player lives back to maximum
}
