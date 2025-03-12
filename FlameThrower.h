#pragma once
#include "Weapon.h"
#include "Objects/MobileObjects/FlameThrowerProjectile.h"

class FlameThrower : public Weapon
{
public:
    FlameThrower();
    FlameThrower(sf::Texture* texture, const sf::Vector2f& position)
        :Weapon(texture, position),
        m_cooldownTime(0.5f),
        m_currentCooldown(0.0f),
        m_range(200.0f),
        m_spreadAngle(30.0f) {};

	~FlameThrower() = default;

    void update(float deltaTime, const sf::Vector2f& mapSize) override;
    std::unique_ptr<Projectile> fire(const sf::Vector2f& startPosition, const sf::Vector2f& direction);
 
    bool isReady() const;
    std::string getAmmoType() const;
    std::string getName() const;
private:
    float m_cooldownTime;
    float m_currentCooldown;
    float m_range;
    float m_spreadAngle;
};