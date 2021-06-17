#include "EndScreen.h"

// Constructor for the end screen 
EndScreen::EndScreen(GameState *gameState, sf::Vector2u window_size)
{
	m_backgroundTex = ResourceManager::instance().m_holder["endBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(window_size.x / 2, window_size.y / 2);
}

// Deconstructor for the end screen
EndScreen::~EndScreen() {}

// Update loop for the end screen
void EndScreen::update(Controller * controller, sf::Time dt)
{

}

// render loop for the end screen
void EndScreen::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
}