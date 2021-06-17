#include "Splash.h"

Splash::Splash(GameState *gameState)
	
{
	m_backgroundTex = ResourceManager::instance().m_holder["SplashBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setScale(1.0f, 1.0f); // Setting the scale of the background sprite
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2); // Setting the background sprite's origin

	m_backgroundSprite.setPosition(1500, 1000); // Setting the background sprite's position
							
	m_state = gameState;
}

Splash::~Splash()
{
}

void Splash::update(Controller * controller, sf::Time dt)
{
	m_controller = controller;
	

	*m_state = GameState::MENU_STATE;
}

void Splash::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_backgroundSprite);
}