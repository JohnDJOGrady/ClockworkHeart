#ifndef ANIMATE_H
#define ANIMATE_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Animate : public sf::Drawable, public sf::Transformable
{
public:
	Animate(sf::Time frame_Time, bool looped, bool playing);
	void setAnimation(Animation& animation);
	Animation* getAnimation() const;
	void setFrameTime(sf::Time time);
	void update(sf::Time dt, sf::Vector2f pos);
	void setTargetFrame(std::size_t frameCount, bool reset = true, sf::Vector2f pos = sf::Vector2f());
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void pause();
	void loop(bool looped);
	void play(Animation &animation);
	void play();
	void stop();

private:
	Animation* m_animation;
	sf::Texture* m_texture;
	sf::Time m_currentTime;
	sf::Time m_frameTime;
	sf::Vector2f m_position;
	std::size_t m_currentFrame;
	bool m_playing;
	bool m_looped;
	sf::Vertex m_vertices[4];
};
#endif //! ANIMATE_H