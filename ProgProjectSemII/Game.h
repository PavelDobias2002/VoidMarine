// Name: Pavel Dobias
// Login: C00301332

// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Globals.h"   // include Global header file
#include "Player.h"   // include Player header file
#include "EnemyMelee.h"	// include header files for enemies and bullets
#include "EnemyRanged.h"
#include "Bullet.h"


class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.

	Player myPlayer;	// player object
	EnemyMelee meleeEnemies[MAX_ENEMYMELEE];	// enemy array of objects
	EnemyRanged rangedEnemies[MAX_ENEMYRANGED];
	Bullet bullet[MAX_BULLETS];	// bullets array for player
	Bullet enemyBullet[MAX_ENEMYBULLETS];	// bullet oject for enemy
	bool restart = false;	// bool for restaring the game

	sf::RenderWindow window;

	bool bulletCollision = false;	// bool for if bullet collision occurs

	sf::Clock m_clock;	// clock for enemy firing
	sf::Time m_interval = sf::microseconds(1000000);	// interval for when enemy fires

	sf::Clock m_respawnClock;	// clock and interval for respawning enemies
	sf::Time m_respawnInterval = sf::microseconds(1250000);

	sf::RectangleShape healthBars[MAX_HEALTHBARS];	// array for health bars

	sf::Sprite bulletSpriteMagazine[MAX_BULLETS];	// sprite and texture for bullet in magazine
	sf::Texture m_bulletTextureMagazine;

	sf::Sprite m_hudSprite;	// sprite and texture for hud
	sf::Texture m_hudTexture;

	sf::Sprite m_backgroundSprite;	// sprite and texture for background
	sf::Texture m_backgroundTexture;

	sf::Sprite m_rkeySprite;	// sprite and texture for r key
	sf::Texture m_rkeyTexture;

	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen

	sf::Text m_scoreText;	// text to write Score:

	sf::Text m_endScore;	// text to show end score

	sf::Text m_endText;	// text to show end message

	sf::Text m_restartText;	// text saying what to do to restart

	sf::Text m_score;	// text to show score
	sf::String m_scorePoints = "";	// string for keeping score
	int m_currentScore = 0;	// variavle for current score

public:
	int m_currentBullet = 0;	// int for firing bullets
	int gameMode = GAME_PLAY;	// varible for different game modes

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	bool	run();
	void	update();
	void	draw();
	void setupGame();	// function setting certain parts of the game

	void checkCollision();	// function which checks collision between player and enemies
	void checkBulletCollision();	// checks if bullet collided with enemy

	void respawnEnemies();	// function to add new enemies after some die

	void countScore();

};
