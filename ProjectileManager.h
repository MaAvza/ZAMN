// ProjectileManager.h
#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Objects/MobileObjects/Projectile.h"
#include "Objects/MobileObjects/ExplosiveProjectile.h"
#include "Objects/MobileObjects/PelletGunProjectile.h"
#include "Objects/MobileObjects/FlameThrowerProjectile.h"

class ProjectileManager
{
public:
    ProjectileManager();

    // move only object
    ProjectileManager(const ProjectileManager&) = delete;
    ProjectileManager& operator=(const ProjectileManager&) = delete;
    ProjectileManager(ProjectileManager&&) = default;
    ProjectileManager& operator=(ProjectileManager&&) = default;

    void addProjectile(std::unique_ptr<Projectile> projectile);
    void update(float deltaTime, const sf::Vector2f& mapSize);
    void draw(sf::RenderWindow& window) const;
    const std::vector<std::unique_ptr<Projectile>>& getProjectiles() const;
    void clear();

private:
    std::vector<std::unique_ptr<Projectile>> m_projectiles;
};


//#pragma once
//#include "Objects/MobileObjects/ExplosiveProjectile.h"
//#include "Objects/MobileObjects/PelletGunProjectile.h"
//#include "Objects/MobileObjects/FlameThrowerProjectile.h"
//#include "Globals.h"
//#include <vector>
//#include <memory>
//#include <algorithm>
//
//class ProjectileManager
//{
//public:
//	ProjectileManager();
//
//	void addProjectile(std::unique_ptr<Projectile> projectile);
//	void update(float deltaTime, const sf::Vector2f& mapSize);
//	void draw(sf::RenderWindow& window) const;
//
//	const std::vector<std::unique_ptr<Projectile>>& getProjectiles() const;
//	void clear();
//
//private:
//	std::vector<std::unique_ptr<Projectile>> m_projectiles;
//};