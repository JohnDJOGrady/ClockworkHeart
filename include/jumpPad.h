#ifndef JUMPPAD_H
#define JUMPPAD_H

#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"

class JumpPad
{
public:
	JumpPad();
	~JumpPad();
	void update();
	void render(sf::RenderWindow & window);
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Sprite m_sprite;
private:
	
	sf::Texture m_texture;
};
#endif // JUMPPAD_H
