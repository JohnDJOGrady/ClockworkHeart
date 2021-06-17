#include "JumpPad.h"

JumpPad::JumpPad()
{
	m_sprite.setPosition(m_position);
	m_texture = ResourceManager::instance().m_holder["JumpPad"];
	m_sprite.setTexture(m_texture);
	m_direction = sf::Vector2f();
}

JumpPad::~JumpPad()
{
	delete this;
}

void JumpPad::update()
{
}

void JumpPad::render(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

