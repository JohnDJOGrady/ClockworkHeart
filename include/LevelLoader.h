#ifndef LEVELLOADER_H
#define LEVELLOADER_H

/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 17/10/2017
/// </summary>

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct ResourceData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
};

struct PlayerData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

struct DoorData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

struct JumpData
{
	sf::Vector2f m_position;	// Its position in the game world.
	sf::Vector2f m_direction;	// Its direction 
};

struct LeverData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

struct NPCData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

struct PlatformData
{
	sf::Vector2f m_position;	// Its position in the game world.
	float m_rotation;
};

struct PressurePlateData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

struct HookData
{
	sf::Vector2f m_position;	// Its position in the game world.
};

// Stores all the yaml objects in the LevelData struct
struct LevelData
{
	std::vector<ResourceData> m_resource;
	std::vector<PlayerData> m_player;
	std::vector<DoorData> m_door;
	std::vector<JumpData> m_jump;
	std::vector<LeverData> m_lever;
	std::vector<NPCData> m_npc;
	std::vector<PlatformData> m_platforms;
	std::vector<PressurePlateData> m_plates;
	std::vector<HookData> m_hook;
};



class LevelLoader
{
public:
	LevelLoader();

	static bool load(int levelNo, LevelData& level);
};
#endif // !LEVELLOADER_H

