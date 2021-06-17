#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"

class Platform
{
public:
	Platform();
	Platform(sf::Vector2f &pos, float rotation);
	~Platform();

	void update();
	void render(sf::RenderWindow &window);

	sf::Vector2f m_position;
	sf::FloatRect dimensions;
	sf::Texture m_texture;
private:
	sf::Sprite m_sprite;
	
};

#endif // !PLATFORM_H