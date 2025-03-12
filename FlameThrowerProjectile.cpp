#include "Objects/MobileObjects/FlameThrowerProjectile.h"

FlameThrowerProjectile::FlameThrowerProjectile(sf::Texture* texture, 
	const sf::Vector2f& position, 
	const sf::Vector2f& direction, 
	float range, 
	float spreadAngle):
	Projectile(texture, position, direction, 500.0f, 20.0f, range), 
    m_spreadAngle(spreadAngle),
    m_innerRadius(25.0f),
    m_outerRadius(50.0f),
    m_edgeDamagePercent(0.5f)
{
    createFlameShape();
}

void FlameThrowerProjectile::update(float deltaTime, const sf::Vector2f& mapSize)
{
    sf::Vector2f movement = m_direction * m_speed * deltaTime;
    m_distanceTraveled += std::sqrt(movement.x * movement.x + movement.y * movement.y);

    if (m_distanceTraveled >= m_maxRange) {
        markForDeletion();
    }
    else {
        move(movement, deltaTime);
    }

    m_flameShape.setPosition(getPosition());
    m_flameShape.setRotation(std::atan2(m_direction.y, m_direction.x) * 180 / 3.14159f);
}

void FlameThrowerProjectile::move(sf::Vector2f velocity, float dt)
{
	setPosition(getPosition() + velocity * dt);
}

void FlameThrowerProjectile::draw(sf::RenderWindow& window) const
{
	window.draw(m_flameShape);
}

float FlameThrowerProjectile::getDamage(const sf::Vector2f& targetPosition) const
{
    sf::Vector2f toTarget = targetPosition - getPosition();
    float distanceToTarget = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (distanceToTarget <= m_innerRadius) {
        return m_damage;
    }
    else if (distanceToTarget <= m_outerRadius) {
        float t = (distanceToTarget - m_innerRadius) / (m_outerRadius - m_innerRadius);
        return m_damage * (1 - t * (1 - m_edgeDamagePercent));
    }
    return 0.0f;
}

bool FlameThrowerProjectile::isInRange(const sf::Vector2f& targetPosition) const
{
    sf::Vector2f toTarget = targetPosition - getPosition();
    float distanceToTarget = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (distanceToTarget <= m_outerRadius) {
        float angle = std::acos(dotProduct(normalize(toTarget), m_direction)) * 180 / 3.14159f;
        return angle <= m_spreadAngle;
    }
    return false;
}

void FlameThrowerProjectile::createFlameShape()
{
    m_flameShape.setPointCount(3);
    m_flameShape.setPoint(0, sf::Vector2f(0, 0));
    m_flameShape.setPoint(1, sf::Vector2f(m_outerRadius, m_outerRadius * std::tan(degToRad(m_spreadAngle))));
    m_flameShape.setPoint(2, sf::Vector2f(m_outerRadius, -m_outerRadius * std::tan(degToRad(m_spreadAngle))));
    m_flameShape.setFillColor(sf::Color(255, 100, 0, 100)); 
}

float FlameThrowerProjectile::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) const
{
    return v1.x * v2.x + v1.y * v2.y;
}

float FlameThrowerProjectile::degToRad(float degrees) const
{
    return degrees * 3.14159f / 180.0f;
}
