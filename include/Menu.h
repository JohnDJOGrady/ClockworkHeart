#ifndef MENU_H
#define MENU_H

/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 18/10/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include <Thor\Resources.hpp>
#include <Aurora/Config.hpp>
#include "ResourceManager.h"
#include "Controller.h"
#include "Screen.h"

enum class ButtonState
{
	NEW_GAME,
	LOAD_GAME,
	OPTIONS_STATE,
	END_STATE
};

class Menu : public Screen
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000); // Initialising the TIME_PER_UPDATE variable for the splash transition.

public:

	Menu(GameState *gameState, sf::Vector2u window_size);	// Constructor for the splash object.
	~Menu();	// Deconstructor for the splash object.

	void update(Controller * controller, sf::Time dt) override;
	void render(sf::RenderWindow & window) override;
	void createUI(sf::Vector2u window_size);

private:
	int m_currentButton;
	GameState *m_state;	// A pointer to the current gamestate
	ButtonState *m_buttonState;

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	sf::Shader m_platShader;	// Shader for the platform
	float m_time;

	Controller * m_controller;	// Pointer to the controller object
	std::vector<Widget*> m_guiElements;
	std::vector<Button*> m_buttons;

};
#endif // !MENU_H
