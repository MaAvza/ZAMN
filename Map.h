#pragma once
#include <iostream>
#include "Objects/Factories/GameObjectFactory.h"
#include "Objects/Factories/EnemySpawner.h"
#include "ResourceManager.h"

class Map
{
public:
	typedef GameObjectFactory::GameObjectPtr ObjectPtr;
	typedef std::vector<ObjectPtr> MapObjects;
	typedef std::vector<std::unique_ptr<Enemy>> EnemyVector;

	Map();
	~Map();

	bool loadFromTmx(const std::string& tmxFile);
	void draw(sf::RenderWindow& window) const;
	void update(float deltaTime);

	const sf::Vector2f& getSize() const;
	void spawnEnemies(); //add enemies to the map

	const MapObjects& getObjects() const;
	const EnemyVector& getEnemies() const;
	const sf::Vector2f& getPlayerSpawnPosition() const;
	void createEnemySamples(); // create "sample" enemies to be cloned
private:
	MapObjects m_mapObjects;
	EnemySpawner m_enemySpawner;
	EnemyVector m_enemies;
	sf::Vector2f m_mapSize;
	sf::Texture m_backgroundTexture;
	sf::Clock m_spawnClock;
	sf::Vector2f m_playerSpawnPosition;

	/*============================*/
	/* tmx file parsing functions */
	/*============================*/
	bool parseMapAttributes(tinyxml2::XMLElement* mapElement);
	bool loadBackgroundImage(tinyxml2::XMLElement* mapElement);
	bool parseObjectLayers(tinyxml2::XMLElement* mapElement);
	bool parseObject(tinyxml2::XMLElement* objectElement);
	/*============================*/

	/*============================*/
	/* object creation functions  */
	void registerObjectFactories();
	void registerEnemySpawnStrategies();
	bool addObject(const std::string& type, const sf::Vector2f& position, const sf::Vector2f& size);
	std::vector<std::unique_ptr<Enemy>> m_enemySamples; 
	/*============================*/
};