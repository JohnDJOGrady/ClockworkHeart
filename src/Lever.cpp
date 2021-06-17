#include "Lever.h"

Lever::Lever()
{
	m_activated = false;
	m_sprite.setPosition(m_position);
	m_inactive = ResourceManager::instance().m_holder["inactive_lever"];
	m_active = ResourceManager::instance().m_holder["active_lever"];
	m_sprite.setTexture(m_inactive);
}

void Lever::update()
{
	
}

void Lever::render(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

void Lever::reset()
{
	m_activated = false;
	m_sprite.setTexture(m_inactive);
}

void Lever::activate()
{
	if (m_activated)
	{
		m_sprite.setTexture(m_inactive);
		m_activated = false;
	}
	else
		m_sprite.setTexture(m_active);
		m_activated = true;
}

