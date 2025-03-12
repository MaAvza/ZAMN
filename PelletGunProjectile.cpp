#include "Objects/MobileObjects/PelletGunProjectile.h"

void PelletGunProjectile::update(float deltaTime, const sf::Vector2f& mapSize)
{
	if (m_isExpired)
	{
		return;
	}

	sf::Vector2f movement = m_direction * m_speed * deltaTime;
	m_distanceTraveled += std::sqrt(movement.x * movement.x + movement.y * movement.y);

	if (m_distanceTraveled >= m_maxRange)
	{
		m_isExpired = true;
		markForDeletion();
		return;
	}

	move(m_direction * m_speed, deltaTime);
}

float PelletGunProjectile::getDamage() const
{
	return m_damage;
}

bool PelletGunProjectile::isExpired() const
{
	return m_isExpired;
}
