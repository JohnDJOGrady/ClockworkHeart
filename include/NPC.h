#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <Thor\Resources.hpp>
#include "Platform.h"
#include "Controller.h"

class NPC
{
public:
	NPC();
	~NPC();
	void update(Controller * controller, sf::Time dt, bool controlled);
	void render(sf::RenderWindow &window);
	void collisions(Platform* entity);
	void checkInput();
	void applyGravity();
	void jump(sf::Vector2f bounce);
	sf::Vector2f* getVel();
	sf::Vector2f* getPos();

	sf::Vector2f m_position;
private:
	
	float lerp(float v0, float v1, float t);
	
	sf::Texture m_currentTexture;
	sf::Sprite m_sprite;

	sf::Texture m_textureArray[7];
	sf::Texture m_spriteSheet, m_spriteSheetLeft, m_spriteSheetRight;

	Animate m_animateSprite = Animate(sf::seconds(.1), true, false);
	Animation* m_currentAnimation;
	Animation m_animateRight, m_animateLeft, m_animateJump, m_animateIdle;
	std::vector<Animation> m_animations;

	int animationCounter = 0;
	int animationIndex = 0;

	float m_red;
	float m_green;
	float m_blue;
	float m_opacity;
	sf::Shader m_shader;
	float m_time = 0.0f;

	sf::Vector2f m_velocity;

	Controller * m_controller;	// Pointer to the controller object

	sf::Texture m_texture;
	sf::Sprite m_sprite2;
};

#endif //!NPC_H
