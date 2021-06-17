#ifndef PLAYER_H
#define PLAYER_H

#include <Thor\Resources.hpp>
#include "ResourceManager.h"
#include "Controller.h"
#include <SFML\Graphics.hpp>
#include "NPC.h"
#include "Platform.h"
#include "Hook.h"

class Player
{
public:
	Player();
	~Player();

	void update(Controller * controller, sf::Time dt, bool controlled);
	void render(sf::RenderWindow & window);
	void collisions(Platform* entity);
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	void applyGravity();
	sf::Vector2f* m_targetVel;
	sf::Vector2f* m_targetPos;

	void jump(sf::Vector2f bounce);
	sf::Sprite m_arrowSprite;

private:
	
	void checkInput();
	float float_Lerp(float v0, float v1, float t);
	sf::Vector2f vector_Lerp(sf::Vector2f point, sf::Vector2f target, float t);

	sf::Texture m_currentTexture;
	sf::Sprite m_sprite;

	sf::Texture m_spriteSheet, m_spriteSheetLeft, m_spriteSheetRight;

	Animate m_animateSprite = Animate(sf::seconds(.1), true, false);
	Animation* m_currentAnimation;
	Animation m_animateRight, m_animateLeft, m_animateJumpR, m_animateJumpL, m_animateIdleL, m_animateIdleR;
	std::vector<Animation> m_animations;
	std::string m_direction = "right";
	
	Controller * m_controller;	// Pointer to the controller object
	Hook* m_hook;
	float m_hookAngle = 45;
	float m_hookTime = 0.0f;

	int animationCounter = 0;
	int animationIndex = 0;

	float m_red;
	float m_green;
	float m_blue;
	float m_opacity;
	sf::Shader m_shader;
	float m_time = 0.0f;

	sf::Texture m_arrowTex;
	float m_alpha = 0.0f;
};
#endif // !PLAYER_H

