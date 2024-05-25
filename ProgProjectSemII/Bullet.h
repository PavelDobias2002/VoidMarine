// Name: Pavel Dobias
// Login: C00301332

#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include "Globals.h"

class Bullet
{
	// private data members

	sf::Texture textureNorth;	// textures changing based on which direction the bullet is fired
	sf::Texture textureSouth;
	sf::Texture textureWest;
	sf::Texture textureEast;
	sf::Sprite bulletSprite;

	int speed;	// speed and direction for bullet shot by player
	int direction;

	sf::Vector2f playerPosition;	// varible to store player pos for targeting

	bool isFiring = false;	// bool for if bullet is fired

	bool playerFiring = false;

public:
	Bullet();	// default constructor

	void setupBullet();	//function which sets up the bullet
	sf::Sprite getBody();	// return the sprite of the bullet

	void setPosition();	// sets position of the bullet
	void setPosition(float xPos, float yPos);	// if we need to set the pos, by passing variables
	sf::Vector2f getPosition();

	void beingFired(float xPos, float yPos, int m_direction);	// function changing the isFiring to true

	void bulletMovement();	// bullet moving when fired

	void checkBoundaries(); // if bullet reaches edges of the screen it stops or explodes

	bool checkFiring(); // function that checks bullet is firing


};