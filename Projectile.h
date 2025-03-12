#pragma once
#include "MobileObject.h"
#include <cmath>

class Projectile : public MobileObject
{
public:
	Projectile(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction,
		float speed, float damage, float maxRange)
		: MobileObject(texture, position),
		m_direction(normalize(direction)),
		m_speed(speed),
		m_damage(damage),
		m_maxRange(maxRange),
		m_distanceTraveled(0.0f) {};

	virtual ~Projectile() = default;

	virtual void update(float deltaTime, const sf::Vector2f& mapSize) = 0;
	void move(sf::Vector2f velocity, float dt) override;

	float getDamage() const;

protected:
	sf::Vector2f m_direction;
	float m_speed;
	float m_damage;
	float m_maxRange;
	float m_distanceTraveled;

	sf::Vector2f normalize(const sf::Vector2f& v) const;
};
