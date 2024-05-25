#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include "Globals.h"
#include <cstdlib>  // for randomazing

class EnemyRanged
{
	// private data members

	sf::Texture textureNorth;	// textures changing based on which direction player is facing
	sf::Texture textureSouth;
	sf::Texture textureWest;
	sf::Texture textureEast;

	sf::Sprite enemySprite;	// sprite for enemy body

	int speed;	// speed, health and direction of the enemy
	int health;
	int direction;

	bool isAlive = true;	// bool telling if enemy is alive

	bool isMoving = false;

	sf::Vector2f m_enemyPos;	// vector for enemy position

public:
	EnemyRanged();	// default constructor

	void setupEnemy();	// sets the texture for the enemy
	sf::Sprite getBody();	// returns the sprite of the enemy for drawing purposes

	void setPosition();	// sets the position of the enemy
	void setPosition(float xPos, float yPos);
	sf::Vector2f getPosition();

	void enemyMovement();	// function for enemy movement

	void checkBoundaries();	// checks if enemy is not crossing boundaries

	int checkDirection();	// checks direction and returns it

	bool checkAlive();	// function that checks if enemy is alive

	void dealDamage(int damage);

	void changeDirection(int randomDirection);	//function whic sets the random direction passed from game.cpp
	bool checkMoving();

	void respawn();
};