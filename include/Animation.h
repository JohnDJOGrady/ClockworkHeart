#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	void setSpriteSheet(sf::Texture& texture);
	sf::Texture* getSpriteSheet();
	void createAnimation(int start_X, int start_Y, int frame_Width, int frame_Height, int frame_Count);
	sf::IntRect getFrame(std::size_t n);
	std::size_t getSize();

private:
	std::vector<sf::IntRect> m_frames;
	sf::Texture* m_texture;
};


#endif //! ANIMATION_H