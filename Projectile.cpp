#pragma once
#include "Objects/MobileObjects/Projectile.h"

void Projectile::move(sf::Vector2f velocity, float dt)
{
	setPosition(getPosition() + velocity);
}

float Projectile::getDamage() const
{
    return m_damage;
}

sf::Vector2f Projectile::normalize(const sf::Vector2f& v) const
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0)
        return sf::Vector2f(v.x / length, v.y / length);
    return v;
}
