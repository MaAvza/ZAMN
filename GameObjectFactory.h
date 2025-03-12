#pragma once
#include "Objects/StaticObjects/Obstacle.h"
#include "Utility/RandomGenerator.h"
#include <unordered_map>
#include <functional>
#include <memory>

class GameObjectFactory
{
public:
	using Creator = std::function<std::unique_ptr<GameObject>(sf::Texture* texture, const sf::Vector2f& pos)>;
	using GameObjectPtr = std::unique_ptr<GameObject>;
	
	static GameObjectFactory& instance();
	static GameObjects::Type stringToObjectType(const std::string& type);
	void registerObject(GameObjects::Type type, Creator creator);

	GameObjectPtr createObject(GameObjects::Type type, sf::Texture* texture, const sf::Vector2f& pos);

private:
	GameObjectFactory() = default;
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;

	std::unordered_map<GameObjects::Type, Creator> m_creators;
};