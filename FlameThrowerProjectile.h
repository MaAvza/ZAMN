#pragma once
#include "Projectile.h"

class FlameThrowerProjectile : public Projectile
{
public:
	FlameThrowerProjectile(sf::Texture* texture, 
		const sf::Vector2f& position, 
		const sf::Vector2f& direction, 
		float range, 
		float spreadAngle);
	~FlameThrowerProjectile() = default;

	void update(float deltaTime, const sf::Vector2f& mapSize) override;
	void move(sf::Vector2f velocity, float dt) override;
	void draw(sf::RenderWindow& window) const;

	float getDamage(const sf::Vector2f& targetPosition) const;
	bool isInRange(const sf::Vector2f& targetPosition) const;

private:
	float m_spreadAngle;
	float m_innerRadius;
	float m_outerRadius;
	float m_edgeDamagePercent;
	sf::ConvexShape m_flameShape;

	void createFlameShape();
	float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
	float degToRad(float degrees) const;
};