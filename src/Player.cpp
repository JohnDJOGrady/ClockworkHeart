#include "Player.h"

Player::Player()
{
	// positions and velocity
	m_position = sf::Vector2f(100, 900);
	m_velocity = sf::Vector2f(0, 0);
	m_targetVel = &m_velocity;
	m_targetPos = &m_position;
	
	// setting up animations & shaders
	m_currentTexture = ResourceManager::instance().m_holder["character1"];
	m_sprite.setTexture(m_currentTexture);
	m_spriteSheet = ResourceManager::instance().m_holder["SpriteSheet"];
	m_spriteSheetLeft = ResourceManager::instance().m_holder["SpriteSheetLeft"];
	m_spriteSheetRight = ResourceManager::instance().m_holder["SpriteSheetRight"];

	m_animateRight.setSpriteSheet(m_spriteSheet);
	m_animateRight.createAnimation(0, 0, 60, 150, 8);
	m_animateLeft.setSpriteSheet(m_spriteSheet);
	m_animateLeft.createAnimation(0, 150, 60, 150, 8);

	m_animateIdleR.setSpriteSheet(m_spriteSheet);
	m_animateIdleR.createAnimation(60, 300, 60, 150, 0);
	m_animateIdleL.setSpriteSheet(m_spriteSheet);
	m_animateIdleL.createAnimation(0, 300, 60, 150, 0);

	m_animateJumpR.setSpriteSheet(m_spriteSheet);
	m_animateJumpR.createAnimation(0, 455, 65, 150, 0);
	m_animateJumpL.setSpriteSheet(m_spriteSheet);
	m_animateJumpL.createAnimation(65, 455, 65, 150, 0);

	m_currentAnimation = &m_animateRight;
	m_animateSprite.setAnimation(*m_currentAnimation);
	m_animateSprite.setFrameTime(sf::seconds(.06));

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

	m_hook = new Hook();

	m_arrowTex = ResourceManager::instance().m_holder["arrow"];
	m_arrowSprite.setTexture(m_arrowTex);
	m_arrowSprite.setPosition(sf::Vector2f(-200, -200));
}

Player::~Player()
{
	delete this;
}

void Player::update(Controller * controller, sf::Time dt, bool controlled)
{
	// movemment and animation updates
	if (m_velocity.x > -0.01 && m_velocity.x < 0.01)
	{
		if (m_direction == "right")
		{
			m_currentAnimation = &m_animateIdleL;
		}
		else
			m_currentAnimation = &m_animateIdleR;

		m_animateSprite.setAnimation(*m_currentAnimation);
		m_animateSprite.play();
	}

	if (!controlled)
	{
		m_red = float_Lerp(1.0f, 0.72f, m_time);
		m_green = float_Lerp(1.0f, 0.25f, m_time);
		m_blue = float_Lerp(1.0f, 0.05f, m_time);
		m_shader.setUniform("red", m_red);
		m_shader.setUniform("green", m_green);
		m_shader.setUniform("blue", m_blue);
		m_time += 0.00001f;
		m_controller = controller;
		checkInput();
	}

	m_position += m_velocity;
	m_animateSprite.update(dt, m_position);

	if(m_targetVel->y == 0)
		m_velocity.x *= 0.99;
	else
		m_velocity.x *= 0.9999;


	// feature updates
	m_hook->update();
	if (m_hook->attached())
	{
		if (m_targetVel->x < 0)
		{
			m_currentAnimation = &m_animateJumpL;
		}

		else
		{
			m_currentAnimation = &m_animateJumpR;
		}
		m_animateSprite.setAnimation(*m_currentAnimation);
		m_animateSprite.play();

		m_hookTime += 0.000001f;
		m_position = vector_Lerp(m_position, m_hook->position(), m_hookTime);
		sf::Vector2f d = m_position - m_hook->position();
		if (sqrt((d.x * d.x) + (d.y * d.y)) <= 40)
		{
			sf::Vector2f dimensions = sf::Vector2f(m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height);
			if (m_hook->climbLeft())
			{
				m_position = m_hook->climbPoint(dimensions);
			}
			if (m_hook->climbRight())
			{
				m_position = m_hook->climbPoint(dimensions);
			}
			m_hook->reset(); // set the grapple to false
			m_hookTime = 0.0f;
		}
	}

	else
	{
		applyGravity();
	}
}

void Player::render(sf::RenderWindow & window)
{
	m_animateSprite.draw(window, &m_shader);
	window.draw(m_arrowSprite);
	m_hook->render(window);
	
}

void Player::checkInput()
{
	if (m_controller->m_currentState.A && !m_controller->m_previousState.A && m_targetVel->y == 0)
	{
		m_targetVel->y -= 0.25;
		if (m_currentAnimation != &m_animateJumpR && m_currentAnimation != &m_animateJumpL)
		{
			if (m_targetVel->x < 0)
			{
				m_currentAnimation = &m_animateJumpL;
			}

			else
			{
				m_currentAnimation = &m_animateJumpR;
			}
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
	}

	if (m_controller->m_currentState.RTrigger && !m_controller->m_previousState.RTrigger && !m_hook->fired())
	{
		m_hook->shoot(m_position);
	}

	if (m_controller->m_currentState.LeftThumbStick.x > 10 && m_targetVel->y == 0)
	{
		if (m_currentAnimation != &m_animateRight)
		{
			m_direction = "right";
			m_currentAnimation = &m_animateRight;
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
		m_targetVel->x += m_controller->m_currentState.LeftThumbStick.x * 0.000015;
	}
	
	if (m_controller->m_currentState.LeftThumbStick.x < -10 && m_targetVel->y == 0)
	{
		if (m_currentAnimation != &m_animateLeft)
		{
			m_direction = "left";
			m_currentAnimation = &m_animateLeft;
			m_animateSprite.setAnimation(*m_currentAnimation);
			m_animateSprite.play();
		}
		m_targetVel->x += m_controller->m_currentState.LeftThumbStick.x * 0.000015;
	}

	if (m_controller->m_currentState.RightThumbStick.y > 10)
	{
		m_hookAngle += 0.05;
		m_hook->updateAngle(m_hookAngle);
		m_hook->m_sprite.setRotation(-m_hookAngle);
		m_alpha = 255;
	}
	else if (m_controller->m_currentState.RightThumbStick.y < -10)
	{
		m_hookAngle -= 0.05;
		m_hook->updateAngle(m_hookAngle);
		m_hook->m_sprite.setRotation(-m_hookAngle);
		m_alpha = 255;
	}
	else
	{
		if(m_alpha > 0)
			m_alpha -= 0.1;
	}

	m_arrowSprite.setPosition(m_position.x + (m_sprite.getLocalBounds().width / 2), m_position.y + (m_sprite.getLocalBounds().height / 2));
	m_arrowSprite.setColor(sf::Color(255, 255, 255, m_alpha));
	m_arrowSprite.setRotation(-m_hookAngle);

	if (m_position.x > 1920 +- m_sprite.getLocalBounds().width)
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

void Player::jump(sf::Vector2f bounce)
{
	m_targetVel->x = bounce.x;
	m_targetVel->y = bounce.y;
}

void Player::applyGravity()
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


void Player::collisions(Platform* entity)
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
			if (m_velocity.y > -0.05)
			{
				m_velocity.y -= 0.05;
			}
			m_velocity.x = -0.1;
		}
		else if (m_position.x > entity->m_position.x + entity->dimensions.width - 2)
		{
			if (m_velocity.y > -0.05)
			{
				m_velocity.y -= 0.05;
			}
			m_velocity.x = 0.1;
		}
	}

	if (m_hook->fired())
	{
		m_hook->collisions(entity);
	}
}

float Player::float_Lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}

sf::Vector2f Player::vector_Lerp(sf::Vector2f point, sf::Vector2f target, float t)
{
	return sf::Vector2f(((1.0f - t) * point) + (t * target));
}


