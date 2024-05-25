// Name: Pavel Dobias
// Login: C00301332

// Player class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include "Globals.h"

class Player
{
	// private data members

	sf::Texture textureNorth;	// textures changing based on which direction player is facing
	sf::Texture textureSouth;
	sf::Texture textureWest;
	sf::Texture textureEast;
	sf::Texture idleTexture;
	sf::Texture deadTexture;

	sf::Sprite playerSprite;	// sprite for player body

	int speed;	// speed, health and direction of the player
	int health;
	int direction;

	bool isAlive = true;

	int m_playerFrame{ -1 };	// -1 to set the frame immidietly
	const int PLAYER_FRAMES = 8;	// the sprite sheet has 8 different variations of gumba
	float m_playerFrameCounter = 0.0f;	// says on which frame we are
	float m_playerFrameIncrement = 1.0f; // changes the current frame by 1f 

public:
	Player();	// default constructor

	void setupPlayer();	// sets the texture for the player
	sf::Sprite getBody();	// returns the sprite of the player for drawing purposes

	void setPosition();	// sets the position of the player
	void setPosition(int xPos, int yPos);
	sf::Vector2f getPosition();

	void playerMovement();	// function for player movement
	void stopMovement();	// function to stop player if keys are not pressed

	void checkBoundaries();

	int checkDirection();	// checks direction and returns it

	void decreaseHealth(int damage);	// function which decreases player health

	bool checkAlive();	// function that checks if player is alive

	int checkHealth();

	void resetLives();
};