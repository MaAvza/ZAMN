#include "Objects/MobileObjects/Enemy.h"
#include "Strategy/PatrolBehavior.h"

Enemy::Enemy()
	: MobileObject(), m_behavior(nullptr)
{
	m_behavior = std::make_unique<PatrolBehavior>(this, sf::Vector2f(0, 0)); 
}

Enemy::Enemy(const Enemy& other)
{
	m_sprite = other.m_sprite;
	m_position = other.m_position;
	m_velocity = other.m_velocity;
	m_targetPosition = other.m_targetPosition;
	m_proxyCircle = other.m_proxyCircle;
	setBehavior(std::make_unique<PatrolBehavior>(this, sf::Vector2f(0, 0)));
}

Enemy::Enemy(sf::Texture* texture, const sf::Vector2f& position)
	: MobileObject(texture, position), m_behavior(nullptr)
{
	m_proxyCircle.setRadius(75);
	m_proxyCircle.setFillColor(sf::Color::Transparent);
	m_proxyCircle.setOrigin(m_proxyCircle.getRadius(), m_proxyCircle.getRadius());
	m_proxyCircle.setPosition(m_sprite.getPosition());
	m_proxyCircle.setOutlineColor(sf::Color::Cyan);
	m_proxyCircle.setOutlineThickness(2);

	m_behavior = std::make_unique<PatrolBehavior>(this, sf::Vector2f(0, 0));
}

void Enemy::update(float deltaTime, const sf::Vector2f& mapSize)
{
	if (m_behavior)
	{
		m_behavior->execute(deltaTime);
	}

	MobileObject::update(deltaTime, mapSize);
	m_proxyCircle.setPosition(m_sprite.getPosition());

}

void Enemy::move(sf::Vector2f velocity, float dt)
{
	dt = std::max(dt, MIN_DELTA_TIME);
	m_velocity = velocity;
	m_targetPosition += velocity * dt * ENEMY_SPEED;
}

void Enemy::setBehavior(std::unique_ptr<Behavior> newBehavior)
{
	m_behavior = std::move(newBehavior);
}

void Enemy::onPlayerPositionUpdate(const sf::Vector2f& playerPosition)
{
	m_targetPosition = playerPosition;
}

void Enemy::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

const sf::CircleShape& Enemy::getProxyCircle() const
{
	return m_proxyCircle;
}

const float Enemy::getProximityRadius() const
{
	return m_proxyCircle.getRadius();
}

float Enemy::getDamageAtContact() const
{
	return m_damageAtContact;
}

bool Enemy::isTargetWithinProximity() const
{
	return m_proxyCircle.getGlobalBounds().contains(m_targetPosition);
}
