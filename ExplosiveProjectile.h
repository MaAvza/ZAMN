#pragma once
#include "Projectile.h"

class ExplosiveProjectile : public Projectile
{
public:
	ExplosiveProjectile(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction,
		float speed, float damage, float maxRange, float explosionRadius, sf::Color explosionColor);

	void update(float deltaTime, const sf::Vector2f& mapSize) override;
	void draw(sf::RenderWindow& window) const override;
	
	void explode();

	bool hasExploded() const;
	float getExplosionRadius();
	float getExplosionTimer();

private:
	float m_explosionRadius;
	bool m_hasExploded;
	float m_explosionTimer = 0.0f;
	sf::CircleShape m_explosionShape;
	sf::Color m_explosionColor;
};