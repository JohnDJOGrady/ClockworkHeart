#include "PressurePlate.h"

PressurePlate::PressurePlate()
{
	m_sprite.setPosition(m_position);
	m_textureOn = ResourceManager::instance().m_holder["onPlate"];
	m_textureOff = ResourceManager::instance().m_holder["offPlate"];
	m_sprite.setTexture(m_textureOff);
}

PressurePlate::~PressurePlate()
{
	delete this;
}

void PressurePlate::update()
{

}

void PressurePlate::setPos(sf::Vector2f pos)
{
	m_position.y = pos.y - m_sprite.getLocalBounds().height;
	m_position.x = pos.x + m_sprite.getLocalBounds().width / 2;
}

void PressurePlate::render(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

void PressurePlate::setActivate(bool activated)
{
	m_activated = activated;
	if (m_activated)
		m_sprite.setTexture(m_textureOn);
	else
		m_sprite.setTexture(m_textureOff);
}
