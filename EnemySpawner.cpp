#include "Objects/Factories/EnemySpawner.h"
#include <Objects/MobileObjects/Zombie.h>
#include <Objects/MobileObjects/GiantAnt.h>
#include <Objects/MobileObjects/TommyTheDoll.h>
#include "Utility/ResourceManager.h"

EnemySpawner::EnemySpawner()
{
    auto defaultStrategy = [](const sf::Vector2f& mapSize, RandomGenerator& rng) {
        return sf::Vector2f(rng.getRandomFloat(0, mapSize.x), rng.getRandomFloat(0, mapSize.y));
        };
    registerSpawnStrategy(Enemies::Name::Zombie, defaultStrategy);
    registerSpawnStrategy(Enemies::Name::GiantAnt, defaultStrategy);
    registerSpawnStrategy(Enemies::Name::TommyTheDoll, defaultStrategy);
}

void EnemySpawner::registerSpawnStrategy(Enemies::Name name, SpawnStrategy strategy)
{
	m_spawnStrategies[name] = std::move(strategy);
}

void EnemySpawner::registerEnemyCreator(Enemies::Name name, EnemyCreator creator)
{
	m_enemyCreators[name] = std::move(creator);
}

std::unique_ptr<Enemy> EnemySpawner::createEnemy(Enemies::Name name, const sf::Vector2f& position)
{
    auto creatorIt = m_enemyCreators.find(name);
    if (creatorIt != m_enemyCreators.end()) {
        return creatorIt->second(position);
    }
    return nullptr;
}

std::vector<std::unique_ptr<Enemy>> EnemySpawner::spawnEnemies(Enemies::Name enemyName, 
	const sf::Vector2f& mapSize, int minEnemies, int maxEnemies)
{
    std::vector<std::unique_ptr<Enemy>> enemies;
    int numEnemies = m_randomGen.getRandomInt(minEnemies, maxEnemies);

    auto spawnStrategyIt = m_spawnStrategies.find(enemyName);
    if (spawnStrategyIt == m_spawnStrategies.end()) 
    {
        // Use a default strategy if none is registered
        spawnStrategyIt = m_spawnStrategies.emplace(enemyName,
            [](const sf::Vector2f& mapSize, RandomGenerator& rng) {
                return sf::Vector2f(rng.getRandomFloat(0, mapSize.x), rng.getRandomFloat(0, mapSize.y));
            }).first;
    }

    auto creatorIt = m_enemyCreators.find(enemyName);
    if (creatorIt == m_enemyCreators.end()) 
    {
        // No creator registered for this enemy type
        return enemies;
    }

    for (int i = 0; i < numEnemies; ++i) {
        sf::Vector2f position = spawnStrategyIt->second(mapSize, m_randomGen);
        auto enemy = creatorIt->second(position);
        if (enemy) {
            enemies.push_back(std::move(enemy));
        }
    }

    return enemies;
}
