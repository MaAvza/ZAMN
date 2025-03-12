#include "Utility\Map.h"
#include <cctype>  
#include <algorithm>  
#include <Objects/StaticObjects/HealthPotion.h>
#include <Objects/StaticObjects/PistolAmmo.h>
#include <Objects/MobileObjects/Survivor.h>
#include <Objects/StaticObjects/Dynamite.h>
#include <Objects/StaticObjects/Key.h>
#include <Objects/StaticObjects/FlameThrowerAmmo.h>
#include <Objects/StaticObjects/FirstAidKit.h>
#include <Objects/StaticObjects/Door.h>
#include <Objects/StaticObjects/Closet.h>
#include <Objects/MobileObjects/Zombie.h>
#include <Objects/MobileObjects/GiantAnt.h>
#include <Objects/MobileObjects/TommyTheDoll.h>
#include <Objects/MobileObjects/MutantPlant.h>

Map::Map()
    : m_backgroundTexture(), m_mapSize(0, 0)
{
    registerObjectFactories();
    m_spawnClock.restart();
}

Map::~Map()
{
}

bool Map::loadFromTmx(const std::string& tmxFile)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile(tmxFile.c_str());

    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading TMX file: " << tmxFile << std::endl;
        return false;
    }

    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "Invalid TMX format: Missing <map> element." << std::endl;
        return false;
    }

    if (!parseMapAttributes(mapElement) ||
        !loadBackgroundImage(mapElement) ||
        !parseObjectLayers(mapElement)) {
        return false;
    }

    if (m_mapObjects.empty()) {
        std::cerr << "No objects found in the TMX file." << std::endl;
        return false;
    }

    return true;
}

bool Map::parseMapAttributes(tinyxml2::XMLElement* mapElement)
{
    int tileWidth = mapElement->IntAttribute("tilewidth", 0);
    int tileHeight = mapElement->IntAttribute("tileheight", 0);
    int mapWidth = mapElement->IntAttribute("width", 0);
    int mapHeight = mapElement->IntAttribute("height", 0);

    if (tileWidth == 0 || tileHeight == 0 || mapWidth == 0 || mapHeight == 0) {
        std::cerr << "Invalid map attributes." << std::endl;
        return false;
    }

    return true;
}

bool Map::loadBackgroundImage(tinyxml2::XMLElement* mapElement)
{
    auto imageLayer = mapElement->FirstChildElement("imagelayer");
    if (!imageLayer) return false;

    auto image = imageLayer->FirstChildElement("image");
    if (!image) return false;

    const char* source = image->Attribute("source");
    if (!source) return false;

    if (!m_backgroundTexture.loadFromFile(source)) {
        std::cout << "Failed to load background image: " << source << std::endl;
        return false;
    }

    m_mapSize.x = image->FloatAttribute("width", m_mapSize.x);
    m_mapSize.y = image->FloatAttribute("height", m_mapSize.y);

    return true;
}

bool Map::parseObjectLayers(tinyxml2::XMLElement* mapElement)
{
    auto objectGroup = mapElement->FirstChildElement("objectgroup");
    if (!objectGroup) {
        std::cout << "No object layers found in the map" << std::endl;
        return false;
    }

    for (auto objectElement = objectGroup->FirstChildElement("object");
        objectElement != nullptr;
        objectElement = objectElement->NextSiblingElement("object"))
    {
        if (!parseObject(objectElement)) {
            std::cout << "Failed to parse an object" << std::endl;
            // Decide whether to return false here or continue parsing other objects
        }
    }

    return true;
}

bool Map::parseObject(tinyxml2::XMLElement* objectElement)
{
    const char* name = objectElement->Attribute("name");

    // If there's no name attribute, ignore this object
    if (!name) {
        return true;
    }

    float x = objectElement->FloatAttribute("x");
    float y = objectElement->FloatAttribute("y");
    float width = objectElement->FloatAttribute("width");
    float height = objectElement->FloatAttribute("height");

    sf::Vector2f position(x, y);
    sf::Vector2f size(width, height);

    if (std::string(name) == "Player") {
        m_playerSpawnPosition = position;
        return true; // We don't need to create a Player object, just store its position
    }

    return addObject(name, position, size);
}

void Map::registerEnemySpawnStrategies()
{
    m_enemySpawner.registerSpawnStrategy(Enemies::Name::Zombie,
        [](const sf::Vector2f& mapSize, RandomGenerator& rng) -> sf::Vector2f {
            float x = rng.getRandomFloat(0.0f, mapSize.x);
            float y = rng.getRandomFloat(0.0f, mapSize.y);
            return sf::Vector2f(x, y);
        }
    );
    m_enemySpawner.registerSpawnStrategy(Enemies::Name::GiantAnt,
		[](const sf::Vector2f& mapSize, RandomGenerator& rng) -> sf::Vector2f {
			float x = rng.getRandomFloat(0.0f, mapSize.x);
			float y = rng.getRandomFloat(0.0f, mapSize.y);
			return sf::Vector2f(x, y);
		}
	);
    m_enemySpawner.registerSpawnStrategy(Enemies::Name::TommyTheDoll,
        [](const sf::Vector2f& mapSize, RandomGenerator& rng) -> sf::Vector2f {
            float x = rng.getRandomFloat(0.0f, mapSize.x);
			float y = rng.getRandomFloat(0.0f, mapSize.y);
			return sf::Vector2f(x, y);
		}
        	);
    /*m_enemySpawner.registerSpawnStrategy(Enemies::Name::MutantPlant,
        [](const sf::Vector2f& mapSize, RandomGenerator& rng) -> sf::Vector2f {
            float x = rng.getRandomFloat(0.0f, mapSize.x);
            float y = rng.getRandomFloat(0.0f, mapSize.y);
            return sf::Vector2f(x, y);
        }
            );*/
}

bool Map::addObject(const std::string& type, const sf::Vector2f& position, const sf::Vector2f& size)
{
    GameObjects::Type objectType = GameObjectFactory::instance().stringToObjectType(type);

    sf::Texture* texture = nullptr;
    auto textureIt = OBJECT_TEXTURE_MAP.find(objectType);
    if (textureIt != OBJECT_TEXTURE_MAP.end()) {
        texture = ResourceManager::getInstance()->getTexture(textureIt->second);
        if (!texture) {
            std::cerr << "Warning: Failed to get texture for object type: " << type << std::endl;
            // Continue with nullptr texture
        }
    }

    auto object = GameObjectFactory::instance().createObject(objectType, texture, position);
    if (object) {
        object->setSize(size);
        m_mapObjects.push_back(std::move(object));
        return true;
    }

    std::cerr << "Failed to create object of type: " << type << std::endl;
    return false;
}

void Map::createEnemySamples()
{
    m_enemySamples.clear();
    m_enemySamples.push_back(std::make_unique<Zombie>(ResourceManager::getInstance()->getTexture("Zombie"), sf::Vector2f(0, 0)));
    m_enemySamples.push_back(std::make_unique<GiantAnt>(ResourceManager::getInstance()->getTexture("GiantAnt"), sf::Vector2f(0, 0)));
    m_enemySamples.push_back(std::make_unique<TommyTheDoll>(ResourceManager::getInstance()->getTexture("TommyTheDoll"), sf::Vector2f(0, 0)));

    // Register enemy creators with the spawner
    for (const auto& sample : m_enemySamples) {
        m_enemySpawner.registerEnemyCreator(sample->getType(), [&sample](const sf::Vector2f& position) {
            return sample->clone(position);
            });
    }
}

void Map::draw(sf::RenderWindow& window) const
{
    sf::Sprite background(m_backgroundTexture);
    window.draw(background);

    for (auto& object : m_mapObjects)
	{
		object->draw(window);
	}

    for (auto& enemy : m_enemies)
    {
        enemy->draw(window);
    }
}

void Map::update(float deltaTime)
{
    for (auto& object : m_mapObjects)
	{
		object->update(deltaTime, m_mapSize);
	}

    for (auto& enemy : m_enemies)
	{
		enemy->update(deltaTime, m_mapSize);
	}

    if (m_spawnClock.getElapsedTime().asSeconds() >= SPAWN_INTERVAL)
    {
        spawnEnemies();
        m_spawnClock.restart();
    }
}

const sf::Vector2f& Map::getSize() const
{
    return m_mapSize;
}

void Map::spawnEnemies()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDis(0, m_enemySamples.size() - 1);

    Enemies::Name enemyType = m_enemySamples[typeDis(gen)]->getType();

    auto newEnemies = m_enemySpawner.spawnEnemies(enemyType, m_mapSize, MIN_ENEMIES, MAX_ENEMIES);
    for (auto& enemy : newEnemies) {
        m_enemies.push_back(std::move(enemy));
    }
}

const Map::MapObjects& Map::getObjects() const
{
    return m_mapObjects;
}

const Map::EnemyVector& Map::getEnemies() const
{
    return m_enemies;
}

const sf::Vector2f& Map::getPlayerSpawnPosition() const
{
    return m_playerSpawnPosition;
}

void Map::registerObjectFactories()
{
    GameObjectFactory& factory = GameObjectFactory::instance();

    factory.registerObject(GameObjects::Type::Obstacle, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Obstacle>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::Closet, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Closet>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::Door, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Door>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::FirstAidKit, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<FirstAidKit>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::HealthPotion, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<HealthPotion>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::PistolAmmo, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<PistolAmmo>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::FlameThrowerAmmo, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<FlameThrowerAmmo>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::Key, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Key>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::Dynamite, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Dynamite>(texture, pos);
        });

    factory.registerObject(GameObjects::Type::Man, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Man);
        });
    factory.registerObject(GameObjects::Type::Baby, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Baby);
        });
    factory.registerObject(GameObjects::Type::Puppy, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Puppy);
        });
    factory.registerObject(GameObjects::Type::Tourists, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Tourists);
        });
    factory.registerObject(GameObjects::Type::Teacher, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Teacher);
        });
    factory.registerObject(GameObjects::Type::Cheerleader, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Survivor>(texture, pos, Survivors::Type::Cheerleader);
        });

    factory.registerObject(GameObjects::Type::Zombie, [](sf::Texture* texture, const sf::Vector2f& pos) {
        return std::make_unique<Zombie>(texture, pos);
		});

    factory.registerObject(GameObjects::Type::GiantAnt, [](sf::Texture* texture, const sf::Vector2f& pos) {
		return std::make_unique<GiantAnt>(texture, pos);
		});

	factory.registerObject(GameObjects::Type::TommyTheDoll, [](sf::Texture* texture, const sf::Vector2f& pos) {
		return std::make_unique<TommyTheDoll>(texture, pos);
		});

	/*factory.registerObject(GameObjects::Type::MutantPlant, [](sf::Texture* texture, const sf::Vector2f& pos) {
		return std::make_unique<MutantPlant>(texture, pos);
		});*/
}
