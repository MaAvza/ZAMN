#pragma once
#include "Utility/Globals.h"
#include "Utility/RandomGenerator.h"
#include "Objects/MobileObjects/Enemy.h"
#include <vector>
#include <functional>
#include <memory>

class EnemySpawner
{
public:
    using SpawnStrategy = std::function<sf::Vector2f(const sf::Vector2f& mapSize, RandomGenerator& rng)>;
    using EnemyCreator = std::function<std::unique_ptr<Enemy>(const sf::Vector2f& position)>;

    EnemySpawner();

    void registerSpawnStrategy(Enemies::Name name, SpawnStrategy strategy);
    void registerEnemyCreator(Enemies::Name name, EnemyCreator creator);
    std::unique_ptr<Enemy> createEnemy(Enemies::Name name, const sf::Vector2f& position);

    std::vector<std::unique_ptr<Enemy>> spawnEnemies(
        Enemies::Name enemyName,
        const sf::Vector2f& mapSize,
        int minEnemies,
        int maxEnemies
    );

private:
    std::unordered_map<Enemies::Name, SpawnStrategy> m_spawnStrategies;
    std::unordered_map<Enemies::Name, EnemyCreator> m_enemyCreators;
    RandomGenerator m_randomGen;
};