#include "Door.h"

Door::Door()
{
	m_activated = false;
	m_closed = false;
	m_sprite.setPosition(m_position);
	m_openTexture = ResourceManager::instance().m_holder["openDoor"];
	m_closedTexture = ResourceManager::instance().m_holder["closedDoor"];
	m_sprite.setTexture(m_openTexture);
}

Door::~Door()
{
	delete this;
}

void Door::update()
{

}

void Door::render(sf::RenderWindow & window)
{
	if (m_closed)
		m_sprite.setTexture(m_closedTexture);
	else
		m_sprite.setTexture(m_openTexture);
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

void Door::activate()
{
	m_activated = true;
	std::cout << m_activated;
}
