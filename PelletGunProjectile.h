#pragma once
#include "Projectile.h"

class PelletGunProjectile : public Projectile
{
public:
    PelletGunProjectile(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction,
        float speed, float damage, float maxRange)
        : Projectile(texture, position, direction, speed, damage, maxRange) {};

    void update(float deltaTime, const sf::Vector2f& mapSize) override;

    float getDamage() const;
    bool isExpired() const;

private:
    bool m_isExpired = false;
};