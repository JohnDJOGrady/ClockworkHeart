#include "LevelLoader.h"

// an operator for receiving the resource data
void operator >> (const YAML::Node& resourceNode, ResourceData& resource)
{
	resource.m_fileName = resourceNode["file"].as<std::string>();
	resource.m_fileID = resourceNode["ID"].as<std::string>();
}

// an operator to receive the data for the player 
void operator >> (const YAML::Node& playerNode, PlayerData& player)
{
	player.m_position.x = playerNode["position"]["x"].as<float>();
	player.m_position.y = playerNode["position"]["y"].as<float>();
}

// an operator to receive the data for the door 
void operator >> (const YAML::Node& doorNode, DoorData& door)
{
	door.m_position.x = doorNode["position"]["x"].as<float>();
	door.m_position.y = doorNode["position"]["y"].as<float>();
}

// an operator to receive the data for the lever 
void operator >> (const YAML::Node& leverNode, LeverData& lever)
{
	lever.m_position.x = leverNode["position"]["x"].as<float>();
	lever.m_position.y = leverNode["position"]["y"].as<float>();
}

// an operator to receive the data for the npc 
void operator >> (const YAML::Node& npcNode, NPCData& npc)
{
	npc.m_position.x = npcNode["position"]["x"].as<float>();
	npc.m_position.y = npcNode["position"]["y"].as<float>();
}

// an operator to receive the data for the platforms 
void operator >> (const YAML::Node& platformNode, PlatformData& platform)
{
	platform.m_position.x = platformNode["position"]["x"].as<float>();
	platform.m_position.y = platformNode["position"]["y"].as<float>();
	platform.m_rotation = platformNode["rotation"].as<float>();
}

// an operator to receive the data for the jump pads 
void operator >> (const YAML::Node& jumpNode, JumpData& jump)
{
	jump.m_position.x = jumpNode["position"]["x"].as<float>();
	jump.m_position.y = jumpNode["position"]["y"].as<float>();
	jump.m_direction.x = jumpNode["direction"]["x"].as<float>();
	jump.m_direction.y = jumpNode["direction"]["y"].as<float>();
}

// an operator to receive the data for the pressure plates 
void operator >> (const YAML::Node& plateNode, PressurePlateData& plate)
{
	plate.m_position.x = plateNode["position"]["x"].as<float>();
	plate.m_position.y = plateNode["position"]["y"].as<float>();
}

// an operator to receive the data for the grappling hook
void operator >> (const YAML::Node& hookNode, HookData& hook)
{
	hook.m_position.x = hookNode["position"]["x"].as<float>();
	hook.m_position.y = hookNode["position"]["y"].as<float>();
}


// an operator to load in the data from the yaml file to the level load system
void operator >> (const YAML::Node& levelNode, LevelData& level)
{	
	
	const YAML::Node& resourceNode = levelNode["resources"].as<YAML::Node>();
	for (unsigned i = 0; i < resourceNode.size(); i++)
	{
		ResourceData resource;
		resourceNode[i] >> resource;
		level.m_resource.push_back(resource);
	}

	const YAML::Node& playerNode = levelNode["player"].as<YAML::Node>();
	for (unsigned i = 0; i < playerNode.size(); i++)
	{
		PlayerData player;
		playerNode[i] >> player;
		level.m_player.push_back(player);
	}

	const YAML::Node& doorNode = levelNode["door"].as<YAML::Node>();
	for (unsigned i = 0; i < doorNode.size(); i++)
	{
		DoorData door;
		doorNode[i] >> door;
		level.m_door.push_back(door);
	}

	const YAML::Node& jumpNode = levelNode["jumpPad"].as<YAML::Node>();
	for (unsigned i = 0; i < jumpNode.size(); i++)
	{
		JumpData jump;
		jumpNode[i] >> jump;
		level.m_jump.push_back(jump);
	}

	const YAML::Node& plateNode = levelNode["pressurePlate"].as<YAML::Node>();
	for (unsigned i = 0; i < plateNode.size(); i++)
	{
		PressurePlateData plate;
		plateNode[i] >> plate;
		level.m_plates.push_back(plate);
	}


	const YAML::Node& leverNode = levelNode["lever"].as<YAML::Node>();
	for (unsigned i = 0; i < leverNode.size(); i++)
	{
		LeverData lever;
		leverNode[i] >> lever;
		level.m_lever.push_back(lever);
	}

	const YAML::Node& npcNode = levelNode["npc"].as<YAML::Node>();
	for (unsigned i = 0; i < npcNode.size(); i++)
	{
		NPCData npc;
		npcNode[i] >> npc;
		level.m_npc.push_back(npc);
	}

	const YAML::Node& platformNode = levelNode["platforms"].as<YAML::Node>();
	for (unsigned i = 0; i < platformNode.size(); i++)
	{
		PlatformData platform;
		platformNode[i] >> platform;
		level.m_platforms.push_back(platform);
	}

	const YAML::Node& hookNode = levelNode["grapplingHook"].as<YAML::Node>();
	for (unsigned i = 0; i < hookNode.size(); i++)
	{
		HookData hook;
		hookNode[i] >> hook;
		level.m_hook.push_back(hook);
	}
}

LevelLoader::LevelLoader()
{
}

bool LevelLoader::load(int levelNo, LevelData& level)
{
	
	// load the levels 
	std::stringstream ss;
	ss << "resources/levels/level";
	ss << levelNo;
	ss << ".yaml";

	// a try-catch to display an error if the files cant be found
	try 
	{
		YAML::Node base = YAML::LoadFile(ss.str());
		if (base.IsNull())
		{
			std::string message("file:" + ss.str() + "not found");
			throw std::exception(message.c_str());
		}
		base >> level;
	}

	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}