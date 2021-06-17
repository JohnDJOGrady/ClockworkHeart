#ifndef PRESSUREPLATE_H
#define PRESSUREPLATE_H

#include <SFML\Graphics.hpp>
#include <Thor\Resources.hpp>
#include "ResourceManager.h"

class PressurePlate
{
public:
	PressurePlate();
	~PressurePlate();

	void update();
	void render(sf::RenderWindow & window);
	void setPos(sf::Vector2f pos);

	// Function to set the activation of the pressure plate
	void setActivate(bool activated); 

	sf::Vector2f m_position;

private:
	sf::Sprite m_sprite;

	sf::Texture m_textureOn;	// The pressed plate texture
	sf::Texture m_textureOff;	// The plate texture when it hasnt been pressed

	bool m_activated; // Whether or not the plate is activated
};
#endif // PRESSUREPLATE_H
