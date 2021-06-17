#ifndef ENDSCREEN_H
#define ENDSCREEN_H


/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 18/10/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include "Screen.h"
#include <Thor\Resources.hpp>

class EndScreen : public Screen
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000); // Initialising the TIME_PER_UPDATE variable for the splash transition.

public:

	EndScreen(GameState *gameState, sf::Vector2u window_size);	// Constructor for the end screen object.
	~EndScreen();	// Deconstructor for the end screen object.

	void update(Controller * controller, sf::Time dt) override;
	void render(sf::RenderWindow & window) override;

private:
	GameState *m_state;	// A pointer to the current gamestate

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Controller * m_controller;	// Pointer to the controller object

};
#endif // !ENDSCREEN_H

