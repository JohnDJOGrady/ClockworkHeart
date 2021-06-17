#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Splash.h"
#include "Menu.h"
#include "Controller.h"
#include "Widget.h"
#include "Play.h"
#include "Player.h"
#include "Options.h"
#include "EndScreen.h"

class Game
{
public:
	Game();
	~Game();
	void run();


private:
	sf::RenderWindow m_window;
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	GameState *m_currentGameState;	// Stores the current game state
	
	Splash *m_splashScreen;
	Menu *m_menuScreen;
	Play *m_playScreen;
	Options *m_optionsScreen;
	EndScreen *m_endScreen;

	LevelData m_level;	// Stores the level object
	Player * m_player;
	Controller m_controller;	// stores the controller object


	sf::Sound m_sound;
};
#endif // !GAME_H

