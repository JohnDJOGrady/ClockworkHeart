#include "Platform.h"
#include <iostream>

Platform::Platform()
{
	delete this;
}

Platform::Platform(sf::Vector2f &pos, float rotation)
{

	m_position = pos;
	m_texture = ResourceManager::instance().m_holder["Platform"];

	if (rotation == 90)
	{
		m_texture = ResourceManager::instance().m_holder["Platform90"];
	}
	
	
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	dimensions = m_sprite.getLocalBounds();
}

Platform::~Platform()
{
	
}

void Platform::update()
{
}

void Platform::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

