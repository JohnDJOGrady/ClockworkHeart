#include "Animation.h"

Animation::Animation() : m_texture(NULL)
{
}

void Animation::setSpriteSheet(sf::Texture & texture)
{
	m_texture = &texture;
}

sf::Texture * Animation::getSpriteSheet()
{
	return m_texture;
}

void Animation::createAnimation(int start_X, int start_Y, int frame_Width, int frame_Height, int frame_Count)
{
	for (int i = 0; i <= frame_Count; i++)
	{
		m_frames.push_back(sf::IntRect(start_X + (i * frame_Width), start_Y, frame_Width, frame_Height));
	}
}

sf::IntRect Animation::getFrame(std::size_t frameIndex)
{
	return m_frames[frameIndex];
}

std::size_t Animation::getSize()
{
	return m_frames.size();
}
