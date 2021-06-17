#include "Hook.h"

Hook::Hook()
{
	m_sprite.setPosition(sf::Vector2f(-200,0));
	m_velocity = sf::Vector2f();
	m_texture = ResourceManager::instance().m_holder["hook"];
	m_90Texture = ResourceManager::instance().m_holder["Platform90"];
	m_sprite.setTexture(m_texture);
	m_launched = false;
	m_attached = false;
}

Hook::~Hook()
{
	delete this;
}

void Hook::update()
{
	if (m_launched && !m_attached)
	{
		m_pos.y -= m_velocity.y;
		m_pos.x += m_velocity.x;

		if (m_pos.x < 0 || m_pos.x > 1920 || m_pos.y > 1080 || m_pos.y < 0)
		{
			reset();
		}
	}
}

void Hook::render(sf::RenderWindow & window)
{
	if (m_launched)
	{
		m_sprite.setPosition(m_pos);
		window.draw(m_sprite);
	}
}


void Hook::shoot(sf::Vector2f startPos)
{
	m_pos = startPos;
	m_launched = true;
	m_velocity.x = MAX_FORCE * std::cos(m_angle * (std::tan(1) * 2) / 180);
	m_velocity.y = MAX_FORCE * sin(m_angle * (std::tan(1) * 2) / 180);
}

void Hook::collisions(Platform * entity)
{
	sf::FloatRect hook_dimen = dimensions();

	if (hook_dimen.left + hook_dimen.width > entity->m_position.x && hook_dimen.left < entity->m_position.x + entity->dimensions.width && hook_dimen.top + hook_dimen.height > entity->m_position.y && hook_dimen.top < entity->m_position.y + entity->dimensions.height)
	{
		if (m_attached == false)
		{
			if (hook_dimen.left + hook_dimen.width < entity->m_position.x + 10 && entity->m_texture.getSize() != m_90Texture.getSize())
			{
				m_climbLeft = true;
				m_climbPoint = sf::Vector2f(entity->m_position.x, entity->m_position.y + (entity->dimensions.height / 2));
			}
			if (hook_dimen.left > entity->m_position.x + entity->dimensions.width - 10 && entity->m_texture.getSize() != m_90Texture.getSize())
			{
				m_climbRight = true;
				m_climbPoint = sf::Vector2f(entity->m_position.x + entity->dimensions.width, entity->m_position.y + (entity->dimensions.height / 2));
			}
			grapple();
		}
	}
}

void Hook::grapple()
{
	m_attached = true;
}

void Hook::reset()
{
	m_attached = false;
	m_launched = false;
	m_climbLeft = false;
	m_climbRight = false;
}

void Hook::setPos(sf::Vector2f pos)
{
	m_pos = pos;
	m_originalPos = pos;
}

void Hook::updateAngle(float angle)
{
	m_angle = angle;
}

sf::Vector2f Hook::position()
{
	return m_pos;
}

sf::Vector2f Hook::destination()
{
	return m_targetPos;
}

sf::Vector2f Hook::start()
{
	return m_originalPos;
}

sf::Vector2f Hook::climbPoint(sf::Vector2f dimesions)
{
	m_climbPoint.y -= dimesions.y / 2;
	if (m_climbLeft)
	{
		m_climbPoint.x -= dimesions.x;
	}

	return m_climbPoint;
}

sf::FloatRect Hook::dimensions()
{
	return sf::FloatRect(m_pos.x, m_pos.y, m_sprite.getLocalBounds().height, m_sprite.getLocalBounds().width);
}

bool Hook::fired()
{
	return m_launched;
}

bool Hook::attached()
{
	return m_attached;
}

bool Hook::climbLeft()
{
	return m_climbLeft;
}

bool Hook::climbRight()
{
	return m_climbRight;
}
