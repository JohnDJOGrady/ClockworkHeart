#ifndef SCREEN_H
#define SCREEN_H
#include <Widget.h>

class Screen
{
public:
	virtual void update(Controller * controller, sf::Time dt) = 0;
	virtual void render(sf::RenderWindow & window) = 0;
};
#endif // !SCREEN_H

