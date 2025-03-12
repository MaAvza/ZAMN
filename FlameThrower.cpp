#include "Objects/StaticObjects/FlameThrower.h"

FlameThrower::FlameThrower()
    : Weapon(nullptr, sf::Vector2f(0, 0)),
	m_cooldownTime(0.5f),
	m_currentCooldown(0.0f),
	m_range(200.0f),
	m_spreadAngle(30.0f)
{
}

void FlameThrower::update(float deltaTime, const sf::Vector2f& mapSize)
{
    if (m_currentCooldown > 0) {
        m_currentCooldown -= deltaTime;
        if (m_currentCooldown < 0) 
            m_currentCooldown = 0;
    }
}

std::unique_ptr<Projectile> FlameThrower::fire(const sf::Vector2f& startPosition, const sf::Vector2f& direction)
{
    if (m_currentCooldown <= 0 && m_ammo > 0) 
    {
        m_currentCooldown = m_cooldownTime;
        m_ammo--;
        return std::make_unique<FlameThrowerProjectile>(nullptr, startPosition, direction, m_range, m_spreadAngle);
    }
    return nullptr;
}

bool FlameThrower::isReady() const
{
    return m_currentCooldown <= 0 && m_ammo > 0;
}

std::string FlameThrower::getAmmoType() const
{
    return "FlameThrowerAmmo";
}

std::string FlameThrower::getName() const
{
    return "FlameThrower";
}

