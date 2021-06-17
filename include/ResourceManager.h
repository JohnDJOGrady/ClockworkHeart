#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 17/10/2017
/// </summary>

#include "Thor\Resources.hpp"
#include <iostream>
#include "LevelLoader.h"
#include "Animate.h"
#include <SFML\Graphics.hpp>

class ResourceManager
{
public:
	static ResourceManager& instance() { return m_instance; }
	void loadData(LevelData &level);
	thor::ResourceHolder<sf::Texture, std::string> m_holder;	// Resource holder for a texture

private: 
	ResourceManager();
	static ResourceManager m_instance;
};


#endif // !RESOURCEMANAGER_H

