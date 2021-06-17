#include "ResourceManager.h"

ResourceManager ResourceManager::m_instance;

ResourceManager::ResourceManager()
{

}

void ResourceManager::loadData(LevelData &level)
{
	// a try-catch for error handling when trying to acquire the data for each object from yaml
	try
	{

		for (ResourceData data : level.m_resource)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}

	}

	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

