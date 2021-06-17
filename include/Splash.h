#ifndef SPLASH_H
#define SPLASH_H

/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 17/10/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include <Thor\Resources.hpp>
#include <Aurora/Config.hpp>
#include "ResourceManager.h"
#include "Controller.h"
#include "Screen.h"

class Splash : public Screen
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000); // Initialising the TIME_PER_UPDATE variable for the splash transition.

public:

	Splash(GameState *gameState);	// Constructor for the splash object.
	~Splash();	// Deconstructor for the splash object.

	virtual void update(Controller * controller, sf::Time dt) override;
	virtual void render(sf::RenderWindow & window) override;

private:

	GameState *m_state;	// A pointer to the current gamestate

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Controller * m_controller;	// Pointer to the controller object

};
#endif // !SPLASH_H
