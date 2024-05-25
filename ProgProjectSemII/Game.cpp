// Name: Pavel Dobias
// Login: C00301332
// Date: 20/03 - 24/04
// Approximate time taken: 20h
// Actual time taken: 50h
//---------------------------------------------------------------------------
// Project description: Void Marine
// You are one of the Void Marines, a thing grown inside the Void, a place where no emotion or feeling exists. 
// Inside a vat prepared to face the horrors of unknown universe, you are unleashed upon the enemy.
// The once numb state of mind preserved in the Void is exchanged by the real space, feeling the reality crushing on them forces the Marine into killing frenzy, purging everything that stands before them.

// ---------------------------------------------------------------------------
// Known Bugs:
// When player holds R and shoots, the firerate is endless.
// Player can fire on the positions where enemy spawns, this instakills the enemy every time it spawns.
// Because of the fact that the bullet collision happens all the time (not once when enemy or player is hit), the bullets instakill everything most of the time. 

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib")

#include "Game.h"   // include Game header file

int main()
{
	bool restart = true;
	while (restart) 
	{
		Game aGame;
		aGame.loadContent();
		restart = aGame.run();
	}

	return 0;
}

Game::Game() : window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
// Default constructor
{
	
}

void Game::loadContent()
// Load the font file & setup the message string
{
	if (gameMode == GAME_PLAY)
	{
		if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
		{
			std::cout << "error with font file file";
		}

		// set up the message string 
		m_message.setFont(m_font);  // set the font for the text
		m_message.setCharacterSize(24); // set the text size
		m_message.setFillColor(sf::Color::White); // set the text colour
		m_message.setPosition(13, 10);  // its position on the screen

		m_score.setFont(m_font);
		m_score.setCharacterSize(24); // set the text size
		m_score.setFillColor(sf::Color::White); // set the text colour
		m_score.setPosition(1460, 10);  // its position on the screen

		m_scoreText.setFont(m_font);
		m_scoreText.setCharacterSize(24); // set the text size
		m_scoreText.setFillColor(sf::Color::White); // set the text colour
		m_scoreText.setPosition(1405, 10);  // its position on the screen

		for (int index = 0; index < MAX_HEALTHBARS; index++)	// loops trough all the health bars
		{
			switch (index)	// switch using the current index
			{
			case 0:	// for each health bar set size, color and position
				healthBars[0].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[0].setPosition(10, 740); // sets the pos of health
				healthBars[0].setFillColor(sf::Color::Red);
				break;
			case 1:
				healthBars[1].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[1].setPosition(65, 740); // sets the pos of health
				healthBars[1].setFillColor(sf::Color::Red);
				break;
			case 2:
				healthBars[2].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[2].setPosition(120, 740); // sets the pos of health
				healthBars[2].setFillColor(sf::Color::Red);
				break;
			case 3:
				healthBars[3].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[3].setPosition(175, 740); // sets the pos of health
				healthBars[3].setFillColor(sf::Color::Yellow);
				break;
			case 4:
				healthBars[4].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[4].setPosition(230, 740); // sets the pos of health
				healthBars[4].setFillColor(sf::Color::Yellow);
				break;
			case 5:
				healthBars[5].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[5].setPosition(285, 740); // sets the pos of health
				healthBars[5].setFillColor(sf::Color::Yellow);
				break;
			case 6:
				healthBars[6].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[6].setPosition(340, 740); // sets the pos of health
				healthBars[6].setFillColor(sf::Color::Green);
				break;
			case 7:
				healthBars[7].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[7].setPosition(395, 740); // sets the pos of health
				healthBars[7].setFillColor(sf::Color::Green);
				break;
			case 8:
				healthBars[8].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[8].setPosition(450, 740); // sets the pos of health
				healthBars[8].setFillColor(sf::Color::Green);
				break;
			case 9:
				healthBars[9].setSize(sf::Vector2f{ 50.0f, 50.0f });
				healthBars[9].setPosition(505, 740); // sets the pos of health
				healthBars[9].setFillColor(sf::Color::Green);
				break;
			}
		}

		if (!m_bulletTextureMagazine.loadFromFile("ASSETS\\TEXTURES\\bulletinmag.png"))
		{
			std::cout << "problem with bullet in mag" << std::endl;
		}
		for (int index = 0; index < MAX_BULLETS; index++)
		{
			bulletSpriteMagazine[index].setTexture(m_bulletTextureMagazine);

			for (int index = 0; index < MAX_BULLETS; index++)	// loops trough all the health bars
			{
				switch (index)	// switch using the current index
				{
				case 0:	// for each bullet in magazine set position
					bulletSpriteMagazine[0].setPosition(1000, 740); // sets the pos of health
					break;
				case 1:
					bulletSpriteMagazine[1].setPosition(1030, 740); // sets the pos of health
					break;
				case 2:
					bulletSpriteMagazine[2].setPosition(1060, 740); // sets the pos of health
					break;
				case 3:
					bulletSpriteMagazine[3].setPosition(1090, 740); // sets the pos of health
					break;
				case 4:
					bulletSpriteMagazine[4].setPosition(1120, 740); // sets the pos of health
					break;
				case 5:
					bulletSpriteMagazine[5].setPosition(1150, 740); // sets the pos of health
					break;
				case 6:
					bulletSpriteMagazine[6].setPosition(1180, 740); // sets the pos of health
					break;
				case 7:
					bulletSpriteMagazine[7].setPosition(1210, 740); // sets the pos of health
					break;
				case 8:
					bulletSpriteMagazine[8].setPosition(1240, 740); // sets the pos of health
					break;
				case 9:
					bulletSpriteMagazine[9].setPosition(1270, 740); // sets the pos of health
					break;
				case 10:
					bulletSpriteMagazine[10].setPosition(1300, 740); // sets the pos of health
					break;
				case 11:
					bulletSpriteMagazine[11].setPosition(1330, 740); // sets the pos of health
					break;
				case 12:
					bulletSpriteMagazine[12].setPosition(1360, 740); // sets the pos of health
					break;
				case 13:
					bulletSpriteMagazine[13].setPosition(1390, 740); // sets the pos of health
					break;
				case 14:
					bulletSpriteMagazine[14].setPosition(1420, 740); // sets the pos of health
					break;

				}
			}
		}

		if (!m_rkeyTexture.loadFromFile("ASSETS\\TEXTURES\\rkey.png"))
		{
			std::cout << "problem loading rkey" << std::endl;
		}
		m_rkeySprite.setTexture(m_rkeyTexture);
		m_rkeySprite.setPosition(950, 740);
 
		m_endScore.setFont(m_font);  // set the font for the text
		m_endScore.setCharacterSize(64); // set the text size
		m_endScore.setFillColor(sf::Color::White); // set the text colour
		m_endScore.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);  // its position on the screen

		m_endText.setFont(m_font);  // set the font for the text
		m_endText.setCharacterSize(64); // set the text size
		m_endText.setFillColor(sf::Color::White); // set the text colour
		m_endText.setPosition(645, 305);  // its position on the screen

		m_restartText.setFont(m_font);  // set the font for the text
		m_restartText.setCharacterSize(64); // set the text size
		m_restartText.setFillColor(sf::Color::Red); // set the text colour
		m_restartText.setPosition(345, 500);  // its position on the screen

		if (!m_hudTexture.loadFromFile("ASSETS\\TEXTURES\\hud.png"))
		{
			std::cout << "problem with hud" << std::endl;
		}
		m_hudSprite.setTexture(m_hudTexture);	// set texture for sprite
		m_hudSprite.setPosition(0.0f, 0.0f);

		if (!m_backgroundTexture.loadFromFile("ASSETS\\TEXTURES\\background.png"))
		{
			std::cout << "problem with hud" << std::endl;
		}
		m_backgroundSprite.setTexture(m_backgroundTexture);	// set texture for sprite
		m_backgroundSprite.setPosition(0.0f, 0.0f);
	}

}


bool Game::run()
// This function contains the main game loop which controls the game. 
{

	srand((int)time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	setupGame();	// function which sets up certain parts of game

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q)
			{
				window.close();
			}
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

	return restart;
}

void Game::update()
// This function takes the keyboard input and updates the game world
{
	// get keyboard input
	bool playerAlive(myPlayer.checkAlive());	// check if player is alive for gameMode purpose
	if (playerAlive == true)	// if player is alive
	{
		gameMode = GAME_PLAY;	// set the game mode to game play
	}
	else
	{
		gameMode = END_GAME;	// if not the game ends
	}

	if (gameMode == GAME_PLAY)
	{
		bool playerAlive(myPlayer.checkAlive());
		if (playerAlive == true)	// if is alive
		{
			if (sf::Keyboard::isKeyPressed)
			{
				myPlayer.playerMovement();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))	// if player presses space
			{
				if (m_currentBullet < MAX_BULLETS)
				{
					int direction(myPlayer.checkDirection());	// get direction of the player
					sf::Vector2f playerPos(myPlayer.getPosition());	// gets the pos of player so the bullet can be set to player position
					bullet[m_currentBullet].beingFired(playerPos.x, playerPos.y, direction);	// passes the pos and direction of the player to being fired function
					m_currentBullet++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))	// if player presses R
			{
				if (m_currentBullet == MAX_BULLETS)	// if all bullets were fired
				{
					m_currentBullet = 0;	// set the current bullet back to 0 = player can fire multiple bullets again
				}
			}

			myPlayer.checkBoundaries();	// function which does not let player leave the screen boundary

			checkCollision();	// function which checks collisions between player and enemies

			// sets the player bullet movement, boundaries and collision with enemies
			for (int index = 0; index < MAX_BULLETS; index++)
			{
				bool isFiring(bullet[index].checkFiring());
				if (isFiring == true)
				{
					for (int index = 0; index < MAX_BULLETS; index++)	// loop trough the bullet array
					{
						bullet[index].bulletMovement();	// passes the direction to the bullet movement
						bullet[index].checkBoundaries(); // function which chekcs if bullet left the screen, player then can fire again
						checkBulletCollision();	// checks if bullet collided with enemy
					}
				}
			}
		}

		// update any game variables here ...

		// sets the enemyMelee movement and boundary checking
		for (int index = 0; index < MAX_ENEMYMELEE; index++)
		{
			bool enemyAlive(meleeEnemies[index].checkAlive());	// if the enemy is alive
			if (enemyAlive == true)
			{
				for (int index = 0; index < MAX_ENEMYMELEE; index++)	// loops trough all the melee enemies
				{
					sf::Vector2f playerPos(myPlayer.getPosition());	// gets the position of the player
					meleeEnemies[index].enemyMovement(playerPos.x, playerPos.y);	// calls enemy movement function with the player position 
				}
				for (int index = 0; index < MAX_ENEMYMELEE; index++)	// loops trough all the melee enemies
				{
					meleeEnemies[index].checkBoundaries();	// sets the boundaries for the enemy
				}
			}
		}

		// sets the enemyRanged
		for (int index = 0; index < MAX_ENEMYRANGED; index++)
		{
			bool enemyAlive(rangedEnemies[index].checkAlive());	// if the enemy is alive
			if (enemyAlive == true)
			{
				for (int index = 0; index < MAX_ENEMYRANGED; index++)	// loops trough all the melee enemies
				{
					rangedEnemies[index].checkBoundaries();	// sets the boundaries for the enemy
				}

				sf::Time elapsed1 = m_clock.getElapsedTime();	// how much time passed

				if (elapsed1 >= m_interval)	// if the time elapsed is bigger then set interval
				{
					m_clock.restart();	// restart the clock for next check
					for (int index = 0; index < MAX_ENEMYRANGED; index++)	// loops trough all the ranged enemies
					{
						int direction = (rand() % 4) + 1;	// sets random direction
						rangedEnemies[index].changeDirection(direction);	// sets that direction to current enemy

						for (int index = 0; index < MAX_ENEMYBULLETS; index++)
						{
							bool enemyFired(enemyBullet[index].checkFiring());	// checks if enemy fired
							if (enemyFired == false)	// check if bullet was not fired yet
							{
								sf::Vector2f enemyPos(rangedEnemies[index].getPosition());	// gets position of the enemy so the bullet can be set up on its pos
								enemyBullet[index].beingFired(enemyPos.x, enemyPos.y, direction);	// passes the pos and direction of the enemy to being fired function
							}
						}

					}


				}
				rangedEnemies[index].enemyMovement();	// calls enemy movement function with the player position 


				for (int index = 0; index < MAX_ENEMYBULLETS; index++)
				{
					bool enemyFired(enemyBullet[index].checkFiring());
					if (enemyFired == true)	// checks if enemy fired
					{
						enemyBullet[index].bulletMovement();	// moves the enemy bullet

						enemyBullet[index].checkBoundaries(); // function which chekcs if bullet left the screen
						checkBulletCollision();	// checks if bullet collided with player
					}
				}
			}
		}

		sf::Time elapsed2 = m_respawnClock.getElapsedTime();	// how much time passed

		if (elapsed2 >= m_respawnInterval)
		{
			m_respawnClock.restart();	// restart the clock for next check
			respawnEnemies();
		}
	}
	else if (gameMode == END_GAME)	// if gameMode is END_GAME
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	// if player presses space
		{
			gameMode = GAME_PLAY;	// game mode is set back to GAME_PLAY
			myPlayer.resetLives();	// resets player lives back to maximum
			window.close();
			restart = true;
		}
	}
}

void Game::draw()
// This function draws the game world
{
	if (gameMode == GAME_PLAY)
	{
		// Clear the screen and draw your game sprites
		window.clear();

		window.draw(m_backgroundSprite);	// draw background

		window.draw(m_hudSprite);	// draw hud

		m_message.setString("Game Play");
		window.draw(m_message);  // write message to the screen

		m_scoreText.setString("Score: ");
		window.draw(m_scoreText);

		m_score.setString(m_scorePoints);
		window.draw(m_score);

		bool playerAlive(myPlayer.checkAlive());
		if (playerAlive == true)	// if player is alive draw him
		{
			window.draw(myPlayer.getBody());  // draw the player object

			// draws the health bar if player is alive
			int playerHealth(myPlayer.checkHealth());	// checks the current health of player

			if (playerHealth >= 200)	// based on the health draw the health bars, less helath player has the less health bars there are
			{
				window.draw(healthBars[9]);
				window.draw(healthBars[8]);
				window.draw(healthBars[7]);
				window.draw(healthBars[6]);
				window.draw(healthBars[5]);
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 180)
			{
				window.draw(healthBars[8]);
				window.draw(healthBars[7]);
				window.draw(healthBars[6]);
				window.draw(healthBars[5]);
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 160)
			{
				window.draw(healthBars[7]);
				window.draw(healthBars[6]);
				window.draw(healthBars[5]);
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 140)
			{
				window.draw(healthBars[6]);
				window.draw(healthBars[5]);
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 120)
			{
				window.draw(healthBars[5]);
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 100)
			{
				window.draw(healthBars[4]);
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 80)
			{
				window.draw(healthBars[3]);
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 60)
			{
				window.draw(healthBars[2]);
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 40)
			{
				window.draw(healthBars[1]);
				window.draw(healthBars[0]);
			}
			else if (playerHealth >= 20)
			{
				window.draw(healthBars[0]);
			}
		}
		else if (playerAlive == false)
		{
			window.draw(myPlayer.getBody()); //draw dead version of the player
		}

		for (int index = 0; index < MAX_BULLETS; index++)
		{
			bool isFiring(bullet[index].checkFiring());
			if (isFiring == true)	// check if that bullet is fired
			{
				for (int index = 0; index < MAX_BULLETS; index++)
				{
					window.draw(bullet[index].getBody()); // draw the bullet
				}
			}
		}

		for (int index = 0; index < MAX_ENEMYBULLETS; index++)
		{
			bool enemyFiring(enemyBullet[index].checkFiring());
			if (enemyFiring == true)	// check if that bullet is fired
			{

				window.draw(enemyBullet[index].getBody()); // draw the bullet

			}
		}

		for (int index = 0; index < MAX_ENEMYMELEE; index++)
		{
			bool enemyAlive(meleeEnemies[index].checkAlive());
			if (enemyAlive == true)
			{
				window.draw(meleeEnemies[index].getBody());	// draw objects in the enemyMelee array
			}
		}

		for (int index = 0; index < MAX_ENEMYRANGED; index++)
		{
			bool enemyAlive(rangedEnemies[index].checkAlive());
			if (enemyAlive == true)
			{
				window.draw(rangedEnemies[index].getBody());	// draw objects in the enemyMelee array
			}
		}

		for (int index = 0; index < MAX_BULLETS; index++)
		{
			if (m_currentBullet >= 14)	// based on the bullet count draw the bullets in magazine, more bullets player fires the more are added
			{
				window.draw(bulletSpriteMagazine[14]);
				window.draw(bulletSpriteMagazine[13]);
				window.draw(bulletSpriteMagazine[12]);
				window.draw(bulletSpriteMagazine[11]);
				window.draw(bulletSpriteMagazine[10]);
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 13)
			{
				window.draw(bulletSpriteMagazine[13]);
				window.draw(bulletSpriteMagazine[12]);
				window.draw(bulletSpriteMagazine[11]);
				window.draw(bulletSpriteMagazine[10]);
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 12)
			{
				window.draw(bulletSpriteMagazine[12]);
				window.draw(bulletSpriteMagazine[11]);
				window.draw(bulletSpriteMagazine[10]);
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 11)
			{
				window.draw(bulletSpriteMagazine[11]);
				window.draw(bulletSpriteMagazine[10]);
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 10)
			{
				window.draw(bulletSpriteMagazine[10]);
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 9)
			{
				window.draw(bulletSpriteMagazine[9]);
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 8)
			{
				window.draw(bulletSpriteMagazine[8]);
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 7)
			{
				window.draw(bulletSpriteMagazine[7]);
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 6)
			{
				window.draw(bulletSpriteMagazine[6]);
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 5)
			{
				window.draw(bulletSpriteMagazine[5]);
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 4)
			{
				window.draw(bulletSpriteMagazine[4]);
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 3)
			{
				window.draw(bulletSpriteMagazine[3]);
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 2)
			{
				window.draw(bulletSpriteMagazine[2]);
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 1)
			{
				window.draw(bulletSpriteMagazine[1]);
				window.draw(bulletSpriteMagazine[0]);
			}
			else if (m_currentBullet >= 0)
			{
				window.draw(bulletSpriteMagazine[0]);
			}
		}

		if (m_currentBullet == 15)	// if all bullets were fired draw R key
		{
			window.draw(m_rkeySprite);
		}

		window.display();
	}
	else if (gameMode = END_GAME)	// if its the end game = player died
	{
		window.clear();	// clear the window of all the enemies

		m_endScore.setString(m_scorePoints);	// shows the score
		window.draw(m_endScore);

		m_endText.setString("Final Score:");
		window.draw(m_endText);

		m_restartText.setString("To purge more abominations press ESCAPE");	// promt for player to restart game
		window.draw(m_restartText);
		
		window.display();
	}
}

void Game::setupGame()
{
	if (gameMode == GAME_PLAY)
	{
		// sets position of all melee enemies
		meleeEnemies[0].setPosition(50.0f, 50.0f);
		meleeEnemies[1].setPosition(1400.0f, 50.0f);
		meleeEnemies[2].setPosition(50.0f, 625.0f);
		meleeEnemies[3].setPosition(1400.0f, 625.0f);
		// sets position of all ranged enemies
		rangedEnemies[0].setPosition(SCREEN_WIDTH / 2.0f, 50.0f);
		rangedEnemies[1].setPosition(1400.0f, SCREEN_HEIGHT / 2.0f);
		rangedEnemies[2].setPosition(SCREEN_WIDTH / 2.0f, 700.0f);
		rangedEnemies[3].setPosition(50.0f, SCREEN_HEIGHT / 2.0f);
	}
}

void Game::checkCollision()
{
	sf::Vector2f playerPos(myPlayer.getPosition());	//get the pos of player

	for (int index = 0; index < MAX_ENEMYMELEE; index++)
	{
		sf::Vector2f meleeEnemyPos(meleeEnemies[index].getPosition());
		// if the position of the player plus the size of the sprite intersects with the position of the enemySprite plus the size of the sprite = collision
		if ((playerPos.x + 64.0f) >= meleeEnemyPos.x && playerPos.x <= (meleeEnemyPos.x + 64.0f) &&
			(playerPos.y + 64.0f) >= meleeEnemyPos.y && playerPos.y <= (meleeEnemyPos.y + 64.0f))
		{
			std::cout << "collision works" << std::endl;

			myPlayer.decreaseHealth(1);	// deals 1 damage to the player
		}
	}

	for (int index = 0; index < MAX_ENEMYRANGED; index++)
	{
		sf::Vector2f rangedEnemyPos(rangedEnemies[index].getPosition());
		// if the position of the player plus the size of the sprite intersects with the position of the enemySprite plus the size of the sprite = collision
		if ((playerPos.x + 64.0f) >= rangedEnemyPos.x && playerPos.x <= (rangedEnemyPos.x + 64.0f) &&
			(playerPos.y + 64.0f) >= rangedEnemyPos.y && playerPos.y <= (rangedEnemyPos.y + 64.0f))
		{
			std::cout << "collision works" << std::endl;

			myPlayer.decreaseHealth(1);	// deals 1 damage to the player
		}
	}
}

void Game::checkBulletCollision()
{
	for (int indexEnemy = 0; indexEnemy < MAX_ENEMYMELEE; indexEnemy++)
	{
		for (int index = 0; index < MAX_BULLETS; index++)
		{
			sf::Vector2f bulletPos(bullet[index].getPosition());	//get the pos of bullet
			sf::Vector2f meleeEnemyPos(meleeEnemies[indexEnemy].getPosition());
			// if the position of the bullet plus the size of the sprite intersects with the position of the enemySprite plus the size of the sprite = collision
			if ((bulletPos.x + 64.0f) >= meleeEnemyPos.x && bulletPos.x <= (meleeEnemyPos.x + 64.0f) &&
				(bulletPos.y + 64.0f) >= meleeEnemyPos.y && bulletPos.y <= (meleeEnemyPos.y + 64.0f))
			{
				std::cout << "collision bullet works" << std::endl;

				meleeEnemies[indexEnemy].dealDamage(1);	// deals 1 damage to the enemy
				bulletCollision = true;

				bool enemyAlive(meleeEnemies[indexEnemy].checkAlive());
				if (enemyAlive == false)	// if enemy died count score
				{
					countScore();
				}
			}
		}
	}

	for (int indexEnemy = 0; indexEnemy < MAX_ENEMYRANGED; indexEnemy++)
	{
		for (int index = 0; index < MAX_BULLETS; index++)
		{
			sf::Vector2f bulletPos(bullet[index].getPosition());	//get the pos of bullet
			sf::Vector2f rangedEnemyPos(rangedEnemies[indexEnemy].getPosition());
			// if the position of the bullet plus the size of the sprite intersects with the position of the enemySprite plus the size of the sprite = collision
			if ((bulletPos.x + 64.0f) >= rangedEnemyPos.x && bulletPos.x <= (rangedEnemyPos.x + 64.0f) &&
				(bulletPos.y + 64.0f) >= rangedEnemyPos.y && bulletPos.y <= (rangedEnemyPos.y + 64.0f))
			{
				std::cout << "collision bullet works" << std::endl;

				rangedEnemies[indexEnemy].dealDamage(1);	// deals 1 damage to the enemy

				bool enemyAlive(rangedEnemies[indexEnemy].checkAlive()); // if enemy died count score
				if (enemyAlive == false)
				{
					countScore();
				}
			}
		}
	}


	for (int index = 0; index < MAX_ENEMYBULLETS; index++)
	{
		sf::Vector2f bulletPos(enemyBullet[index].getPosition());	//get the pos of bullet
		sf::Vector2f playerPos(myPlayer.getPosition());
		// if the position of the bullet plus the size of the sprite intersects with the position of the enemySprite plus the size of the sprite = collision
		if ((bulletPos.x + 64.0f) >= playerPos.x && bulletPos.x <= (playerPos.x + 64.0f) &&
			(bulletPos.y + 64.0f) >= playerPos.y && bulletPos.y <= (playerPos.y + 64.0f))
		{
			std::cout << "collision bullet works" << std::endl;

			myPlayer.decreaseHealth(1);	// deals 1 damage to the enemy

		}
	}
}

void Game::respawnEnemies()
{
	for (int index = 0; index < MAX_ENEMYMELEE; index++)
	{
		bool enemyAlive(meleeEnemies[index].checkAlive());	// checks if enemy is alive

		if (enemyAlive == false)	// if not
		{
			meleeEnemies[index].respawn();	// call respawn function for current enemy
			switch (index)
			{
				case 0:
					meleeEnemies[0].setPosition(50.0f, 50.0f);	// based on the current enemy index set that enemy to pos
					break;
				case 1:
					meleeEnemies[1].setPosition(1400.0f, 50.0f);
					break;
				case 2:
					meleeEnemies[2].setPosition(50.0f, 625.0f);
					break;
				case 3:
					meleeEnemies[3].setPosition(1400.0f, 625.0f);
					break;
			}
		}
	}
	// same for ranged enemy
	for (int index = 0; index < MAX_ENEMYRANGED; index++)
	{
		bool enemyAlive(rangedEnemies[index].checkAlive());

		if (enemyAlive == false)
		{
			rangedEnemies[index].respawn();
			switch (index)
			{
			case 0:
				rangedEnemies[0].setPosition(SCREEN_WIDTH / 2.0f, 50.0f);
				break;
			case 1:
				rangedEnemies[1].setPosition(1400.0f, SCREEN_HEIGHT / 2.0f);
				break;
			case 2:
				rangedEnemies[2].setPosition(SCREEN_WIDTH / 2.0f, 700.0f);
				break;
			case 3:
				rangedEnemies[3].setPosition(50.0f, SCREEN_HEIGHT / 2.0f);
				break;
			}
		}
	}
}

void Game::countScore()
{
	m_currentScore = m_currentScore++;	// add to 1 current score
	m_scorePoints = std::to_string(m_currentScore);	// change it to string
}









