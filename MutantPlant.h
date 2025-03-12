#pragma once
#include "Enemy.h"
#include "Utility/ResourceManager.h"
#include "Utility/ProjectileManager.h"
class MutantPlant : public Enemy
{
public:
    MutantPlant(sf::Texture* texture,
        const sf::Vector2f& position,
        float shootInterval,
        float projectileSpeed,
        float projectileDamage,
        ProjectileManager& projectileManager);

    MutantPlant(const MutantPlant& other, ProjectileManager& newProjectileManager);

    void update(float deltaTime, const sf::Vector2f& mapSize) override;
    
    std::unique_ptr<Enemy> clone(const sf::Vector2f& position) const override;
    Enemies::Name getType() const override;

private:
    void shootRandomly();

    float m_shootInterval;
    float m_shootTimer;
    float m_projectileSpeed;
    float m_projectileDamage;
    ProjectileManager& m_projectileManager;
};
