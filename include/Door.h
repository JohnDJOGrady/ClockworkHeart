#ifndef DOOR_H
#define DOOR_H

#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"

class Door
{
public:
	Door();
	~Door();
	void update();
	void render(sf::RenderWindow & window);
	bool m_activated;
	void activate();
	bool m_closed;
	sf::Vector2f m_position;

private:
	sf::Sprite m_sprite;
	sf::Texture m_openTexture;
	sf::Texture m_closedTexture;
};
#endif // !DOOR_H

