#ifndef LEVER_H
#define LEVER_H
#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"

class Lever
{
public:
	Lever();
	~Lever() {};
	void update();
	void render(sf::RenderWindow & window);
	void activate();
	void reset();

	sf::Vector2f m_position;
	bool m_activated;
	void nextLevel(int level);
private:
	sf::Sprite m_sprite;
	sf::Texture m_inactive, m_active;
};
#endif // !LEVER_H

