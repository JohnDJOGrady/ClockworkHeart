/// <summary>
/// 3rd Year Project
/// A Clockwork Heart
/// 
/// @author Peter Daly and John O'Grady
/// @date September 2017
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"lib/libyaml-cppmdd") 
#pragma comment(lib,"lib/thor-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"libyaml-cppmd")
#pragma comment(lib,"lib/thor.lib") 
#endif 

#include <iostream>
#include "SFML\Graphics.hpp"
#include "Game.h"


/// <summary>
/// main enrtry point
/// </summary>
/// <returns>zero</returns>
int main()
{
	Game game;
	game.run();
	return 0;
}