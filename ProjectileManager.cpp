// ProjectileManager.cpp
#include "Utility/ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
}

void ProjectileManager::addProjectile(std::unique_ptr<Projectile> projectile)
{
    m_projectiles.emplace_back(std::move(projectile));
}

void ProjectileManager::update(float deltaTime, const sf::Vector2f& mapSize)
{
    for (auto& projectile : m_projectiles)
    {
        projectile->update(deltaTime, mapSize);

        // Handle specific projectile types
        if (auto* explosiveProj = dynamic_cast<ExplosiveProjectile*>(projectile.get()))
        {
            if (explosiveProj->hasExploded() && explosiveProj->getExplosionTimer() > 0.5f)
            {
                explosiveProj->markForDeletion();
            }
        }
        else if (auto* pelletProj = dynamic_cast<PelletGunProjectile*>(projectile.get()))
        {
            if (pelletProj->isExpired())
            {
                pelletProj->markForDeletion();
            }
        }
        // FlameThrowerProjectile doesn't have a specific expiration condition in the provided code
    }

    // Remove projectiles marked for deletion
    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](const std::unique_ptr<Projectile>& projectile) {
                return projectile->isMarkedForDeletion();
            }),
        m_projectiles.end()
    );
}

void ProjectileManager::draw(sf::RenderWindow& window) const
{
    for (const auto& projectile : m_projectiles)
    {
        projectile->draw(window);
    }
}

const std::vector<std::unique_ptr<Projectile>>& ProjectileManager::getProjectiles() const
{
    return m_projectiles;
}

void ProjectileManager::clear()
{
    m_projectiles.clear();
}


//#include "Utility/ProjectileManager.h"
//
//ProjectileManager::ProjectileManager()
//{
//}
//
//void ProjectileManager::addProjectile(std::unique_ptr<Projectile> projectile)
//{
//	m_projectiles.emplace_back(std::move(projectile));
//}
//
//void ProjectileManager::update(float deltaTime, const sf::Vector2f& mapSize)
//{
//    for (auto& projectile : m_projectiles)
//    {
//        projectile->update(deltaTime, mapSize);
//
//        // Handle specific projectile types
//        if (auto* explosiveProj = dynamic_cast<ExplosiveProjectile*>(projectile.get()))
//        {
//            if (explosiveProj->hasExploded() && explosiveProj->getExplosionTimer() > 0.5f)
//            {
//                explosiveProj->markForDeletion();
//            }
//        }
//        else if (auto* pelletProj = dynamic_cast<PelletGunProjectile*>(projectile.get()))
//        {
//            if (pelletProj->isExpired())
//            {
//                pelletProj->markForDeletion();
//            }
//        }
//        // FlameThrowerProjectile doesn't have a specific expiration condition in the provided code
//    }
//
//    // Remove projectiles marked for deletion
//    m_projectiles.erase(
//        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
//            [](const auto& projectile) {
//                return projectile->isMarkedForDeletion();
//            }),
//        m_projectiles.end()
//    );
//}
//
//void ProjectileManager::draw(sf::RenderWindow& window) const
//{
//    for (const auto& projectile : m_projectiles)
//    {
//        projectile->draw(window);
//    }
//}
//
//const std::vector<std::unique_ptr<Projectile>>& ProjectileManager::getProjectiles() const
//{
//	return m_projectiles;
//}
//
//void ProjectileManager::clear()
//{
//    m_projectiles.clear();
//}
