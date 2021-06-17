#include "NPC.h"

NPC::NPC()
{
	m_currentTexture = ResourceManager::instance().m_holder["character1"];
	m_sprite.setTexture(m_currentTexture);
	m_position = sf::Vector2f(500, 900);
	m_velocity = sf::Vector2f(0, 0);
	m_sprite.setPosition(m_position);
	m_spriteSheet = ResourceManager::instance().m_holder["SpriteSheet"];
	m_spriteSheetLeft = ResourceManager::instance().m_holder["SpriteSheetLeft"];
	m_spriteSheetRight = ResourceManager::instance().m_holder["SpriteSheetRight"];


	m_animateRight.setSpriteSheet(m_spriteSheet);
	m_animateRight.createAnimation(0, 0, 60, 150, 8);
	m_animateLeft.setSpriteSheet(m_spriteSheet);
	m_animateLeft.createAnimation(0, 150, 60, 150, 8);
	m_animateIdle.setSpriteSheet(m_spriteSheet);
	m_animateIdle.createAnimation(0, 300, 60, 150, 0);
	m_animateJump.setSpriteSheet(m_spriteSheet);
	m_animateJump.createAnimation(0, 450, 60, 150, 0);
	m_currentAnimation = &m_animateRight;
	m_animateSprite.setAnimation(*m_currentAnimation);
	m_animateSprite.setFrameTime(sf::seconds(.06));

	m_textureArray[0] = ResourceManager::instance().m_holder["character1"];
	m_textureArray[1] = ResourceManager::instance().m_holder["character2"];
	m_textureArray[2] = ResourceManager::instance().m_holder["character3"];
	m_textureArray[3] = ResourceManager::instance().m_holder["character4"];
	m_textureArray[4] = ResourceManager::instance().m_holder["character5"];
	m_textureArray[5] = ResourceManager::instance().m_holder["character6"];
	m_textureArray[6] = ResourceManager::instance().m_holder["character7"];

	m_red = 1.0f;
	m_green = 1.0f;
	m_blue = 1.0f;
	m_opacity = 1.0f;

	if (!m_shader.loadFromFile("shader.vert.txt", "shader.frag.txt"))
		std::cout << "Shader not loaded";

	m_shader.setUniform("texture", m_spriteSheet); //shader.vert
	m_shader.setUniform("opacity", m_opacity);
	m_shader.setUniform("red", m_red);
	m_shader.setUniform("green", m_green);
	m_shader.setUniform("blue", m_blue);
}

NPC::~NPC()
{
	delete this;
}

void NPC::update(Controller * controller,sf::Time dt, bool controlled)
{
	if (m_velocity.x > -0.01 && m_velocity.x < 0.01)
	{
		m_currentAnimation = &m_animateIdle;
		m_animateSprite.setAnimation(*m_currentAnimation);
		m_animateSprite.play();
	}
	if (!controlled)
	{
		m_red = lerp(1.0f, 0.72f, m_time);
		m_green = lerp(1.0f, 0.25f, m_time);
		m_blue = lerp(1.0f, 0.05f, m_time);
		m_shader.setUniform("red", m_red);
		m_shader.setUniform("green", m_green);
		m_shader.setUniform("blue", m_blue);
		m_time += 0.00001f;
		m_controller = controller;
		checkInput();
	}

	m_sprite.setTexture(m_currentTexture);
	//updateSprite();
	
	m_position += m_velocity;
	//m_sprite.setPosition(m_position);
	m_animateSprite.update(dt, m_position);
	if (m_velocity.y == 0)
		m_velocity.x *= 0.99;
	else
		m_velocity.x *= 0.9999;
	applyGravity();
}

void NPC::checkInput()
{
	

	if (m_controller->m_currentState.A && !m_controller->m_previousState.A && m_velocity.y == 0)
	{
		if (m_currentAnimation != &m_animateJump)
		{
			m_currentAnimation = &m_animateJump;
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
		m_velocity.y -= 0.25;
	}


	if (m_controller->m_currentState.LeftThumbStick.x > 10 && m_velocity.y == 0)
	{
		if (m_currentAnimation != &m_animateRight)
		{
			m_currentAnimation = &m_animateRight;
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
		m_velocity.x += m_controller->m_currentState.LeftThumbStick.x * 0.000015;
	}

	if (m_controller->m_currentState.LeftThumbStick.x < -10 && m_velocity.y == 0)
	{
		if (m_currentAnimation != &m_animateLeft)
		{
			m_currentAnimation = &m_animateLeft;
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
		m_velocity.x += m_controller->m_currentState.LeftThumbStick.x * 0.000015;
	}

	if (m_position.x > 1920 + -m_sprite.getLocalBounds().width)
	{
		m_velocity.x = 0;
		m_position.x = 1920 + -m_sprite.getLocalBounds().width;
	}

	if (m_position.x < 0)
	{
		m_velocity.x = 0;
		m_position.x = 0;
	}
}

void NPC::render(sf::RenderWindow &window)
{
	m_animateSprite.draw(window, &m_shader);
	//window.draw(m_sprite2, &m_shader);
}

sf::Vector2f * NPC::getVel()
{
	return &m_velocity;
}

sf::Vector2f * NPC::getPos()
{
	return &m_position;
}

void NPC::applyGravity()
{
	if (m_position.y < 1080 - m_sprite.getLocalBounds().height)
	{
		m_velocity.y += 0.0001;
	}
	else
	{
		m_velocity.y = 0;
	}
}

void NPC::jump(sf::Vector2f bounce)
{
	m_velocity.x = bounce.x;
	m_velocity.y = bounce.y;
}

void NPC::collisions(Platform* entity)
{
	sf::FloatRect dimensions = m_sprite.getLocalBounds();
	if (m_position.x + dimensions.width > entity->m_position.x && m_position.x < entity->m_position.x + entity->dimensions.width && m_position.y + dimensions.height > entity->m_position.y && m_position.y < entity->m_position.y + entity->dimensions.height)
	{
		if (m_position.y + dimensions.height - 2 < entity->m_position.y)
		{
			m_velocity.y = 0;
		}
		else if (m_position.y > entity->m_position.y + entity->dimensions.height - 2)
		{
			m_velocity.y *= -1;
		}

		else if (m_position.x + dimensions.width - 2 < entity->m_position.x)
		{
			m_velocity.y -= 0.08;
			m_velocity.x = -0.1;
		}
		else if (m_position.x > entity->m_position.x + entity->dimensions.width - 2)
		{
			m_velocity.y -= 0.08;
			m_velocity.x = 0.1;
		}
	}
}

float NPC::lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}