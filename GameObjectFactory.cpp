#include "Objects/Factories/GameObjectFactory.h"

GameObjectFactory& GameObjectFactory::instance()
{
    static GameObjectFactory instance;
    return instance;
}

GameObjects::Type GameObjectFactory::stringToObjectType(const std::string& type)
{
    auto it = stringToTypeMap.find(type);
    if (it != stringToTypeMap.end()) {
		return it->second;
	}
    return GameObjects::Type::Obstacle; // Return Obstacle by default
}

void GameObjectFactory::registerObject(GameObjects::Type type, Creator creator)
{
	m_creators[type] = std::move(creator);
}

GameObjectFactory::GameObjectPtr GameObjectFactory::createObject(GameObjects::Type type, 
    sf::Texture* texture, const sf::Vector2f& pos)
{
    auto it = m_creators.find(type);
    if (it != m_creators.end()) {
        return it->second(texture, pos);
    }
    return nullptr;
}
