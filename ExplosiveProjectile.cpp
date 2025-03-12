#include "Objects/MobileObjects/ExplosiveProjectile.h"

ExplosiveProjectile::ExplosiveProjectile(sf::Texture* texture, 
	const sf::Vector2f& position, 
	const sf::Vector2f& direction, 
	float speed, float damage, 
	float maxRange, 
	float explosionRadius, 
	sf::Color explosionColor)
	: Projectile(texture, position, direction, speed, damage, maxRange),
	m_explosionRadius(explosionRadius),
	m_explosionColor(explosionColor),
	m_hasExploded(false)
{
	m_explosionShape.setRadius(m_explosionRadius);
	m_explosionShape.setFillColor(m_explosionColor);
	m_explosionShape.setOrigin(m_explosionRadius, m_explosionRadius);
	m_explosionShape.setPosition(position);
}

void ExplosiveProjectile::update(float deltaTime, const sf::Vector2f& mapSize)
{
	if (m_hasExploded)
	{
		m_explosionTimer += deltaTime;
		return;
	}

	sf::Vector2f movement = m_direction * m_speed * deltaTime;
	move(movement, deltaTime);

	m_distanceTraveled += std::sqrt(movement.x * movement.x + movement.y * movement.y);

	if (m_distanceTraveled >= m_maxRange)
	{
		explode();
	}

	// Update explosion shape position
	m_explosionShape.setPosition(getPosition());
}

void ExplosiveProjectile::draw(sf::RenderWindow& window) const
{
	if (m_hasExploded)
	{
		window.draw(m_explosionShape);
	}
	else
	{
		Projectile::draw(window);
	}
}

void ExplosiveProjectile::explode()
{
	m_hasExploded = true;
	m_explosionTimer = 0.0f;
}

bool ExplosiveProjectile::hasExploded() const
{
	return m_hasExploded;
}

float ExplosiveProjectile::getExplosionRadius()
{
	return m_explosionRadius;
}

float ExplosiveProjectile::getExplosionTimer()
{
	return m_explosionTimer;
}
