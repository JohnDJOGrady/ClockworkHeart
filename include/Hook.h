#ifndef HOOK_H
#define HOOK_H

#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"
#include "Platform.h"

static const float MAX_FORCE = .5;

class Hook
{
public:
	Hook();
	~Hook();

	void update();
	void render(sf::RenderWindow & window);
	void shoot(sf::Vector2f startPos);
	void Hook::collisions(Platform * entity);
	void grapple();
	void reset();
	void setPos(sf::Vector2f pos);
	void updateAngle(float angle);

	// getter methods
	sf::Vector2f position();
	sf::Vector2f destination();
	sf::Vector2f start();
	sf::Vector2f climbPoint(sf::Vector2f pos);

	sf::FloatRect dimensions();

	bool fired();
	bool attached();
	bool climbLeft();
	bool climbRight();
	sf::Sprite m_sprite, m_targetSprite;

private:
	sf::Vector2f m_pos, m_targetPos, m_originalPos, m_velocity, m_climbPoint;

	float m_angle;

	bool m_launched, m_attached, m_climbRight, m_climbLeft;

	
	sf::Texture m_texture, m_90Texture;
};
#endif // !Hook_h

/* EDITS TO ADD
ANGLE UP
ANGLE DOWN
*/