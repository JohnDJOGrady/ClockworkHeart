#include "Animate.h"

Animate::Animate(sf::Time frame_Time, bool looped, bool playing)
{
	m_texture = NULL;
	m_frameTime = frame_Time;
	m_looped = looped;
	m_playing = playing;
	m_currentFrame = 0;
}

// sets the animation texture for the current sprite
void Animate::setAnimation(Animation & animation)
{
	m_animation = &animation;
	m_texture = m_animation->getSpriteSheet();
	m_currentFrame = 0;
	setTargetFrame(m_currentFrame,false, m_position);
}

Animation * Animate::getAnimation() const
{
	return m_animation;
}

// sets the desired frame time for the sprites animation
void Animate::setFrameTime(sf::Time time)
{
	m_frameTime = time;
}

// updates the current animation sheet, progressing to the next frame in the sheet if the
// timer goes beyond a certain point
void Animate::update(sf::Time dt, sf::Vector2f pos)
{
	m_position = pos;
	if (m_playing && m_animation)
	{
		m_currentTime += dt;

		if (m_currentTime >= m_frameTime)
		{
			// reset the time but keep the remainder from current time if there was any
			m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());

			if (m_currentFrame + 1 < m_animation->getSize())
			{
				m_currentFrame++;
			}
			else
			{
				m_currentFrame = 0; // reset frame cycle
				if (!m_looped)
				{
					m_playing = false;
				}
			}
			setTargetFrame(m_currentFrame, false, m_position);
		}
	}
}

// sets the frame of the animation sheet to be rendered to the frame number passed
void Animate::setTargetFrame(std::size_t frameCount, bool reset, sf::Vector2f pos)
{
	if (m_animation)
	{
		// interpolating the width, height and coords for the texture to be rendered
		// acting as pins points for the texture to be rendered to the vertices
		sf::IntRect rect = m_animation->getFrame(frameCount);
		float width, height, left, top, bottom, right;
		width = rect.width;
		height = rect.height;
		left = rect.left;
		right = left + width;
		top = rect.top;
		bottom = top + height;

		m_vertices[0].position = sf::Vector2f(pos.x, pos.y);
		m_vertices[0].texCoords = sf::Vector2f(left, top);

		m_vertices[1].position = sf::Vector2f(pos.x,pos.y + height);
		m_vertices[1].texCoords = sf::Vector2f(left, bottom);

		m_vertices[2].position = sf::Vector2f(pos.x + width, pos.y + height);
		m_vertices[2].texCoords = sf::Vector2f(right, bottom);

		m_vertices[3].position = sf::Vector2f(pos.x + width, pos.y);
		m_vertices[3].texCoords = sf::Vector2f(right, top);

		if(reset)
		{
			// reset the timer to zero so the animation last the full amount of time
			// allocated to frames per second
			m_currentTime = sf::Time::Zero;
		}	
	}
}

void Animate::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (m_animation && m_texture)
	{
		state.transform *= getTransform();
		state.texture = m_texture;
		target.draw(m_vertices, 4, sf::Quads, state);
	}
}

void Animate::pause()
{
	m_playing = false;
}

void Animate::loop(bool looped)
{
	m_looped = looped;
}

void Animate::play(Animation &animation)
{
	if (getAnimation() != &animation)
		setAnimation(animation);
	play();
}

void Animate::play()
{
	m_playing = true;
}

void Animate::stop()
{
	m_playing = false;
	m_currentFrame = 0;
	setTargetFrame(m_currentFrame);
}
