#include "Objects/MobileObjects/MobileObject.h"

MobileObject::MobileObject() : GameObject(), m_velocity(0.0f, 0.0f), m_targetPosition(0,0), m_health(100.0f) {}

MobileObject::MobileObject(sf::Texture* texture, const sf::Vector2f& position)
    : GameObject(texture, position), m_velocity(0.0f, 0.0f), m_targetPosition(position), m_health(100.0f) {}

MobileObject::~MobileObject() {}

void MobileObject::update(float deltaTime, const sf::Vector2f& mapSize) 
{
    
    if (!checkAndHandleBoundaryCollision(m_targetPosition, mapSize))
    {
        setPosition(m_targetPosition);
    }
    else
        m_velocity = sf::Vector2f(0, 0);
}

void MobileObject::draw(sf::RenderWindow& window) const {

    window.draw(m_sprite);
}

void MobileObject::handleInput(sf::Event event, float dt) {
    // Implementation of input handling logic
}

const sf::Vector2f& MobileObject::getPosition() const
{
    return m_position;
}

void MobileObject::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_sprite.setPosition(position);
}

void MobileObject::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

const sf::Vector2f& MobileObject::getVelocity() const
{
    return m_velocity;
}

void MobileObject::hit(float damage)
{
    if (m_health - damage <= 0)
	{
		m_health = 0;
	}
	else
	{
		m_health -= damage;
	}
}

float MobileObject::getHealth() const
{
    return m_health;
}

void MobileObject::setHealth(float health)
{
	m_health = health;
}

bool MobileObject::checkAndHandleBoundaryCollision(const sf::Vector2f& newPosition, const sf::Vector2f& mapSize)
{
    sf::Vector2f objectSize = m_size; // Assuming m_size is the object's size
    bool collision = false;

    sf::Vector2f adjustedPosition = newPosition;

    // Check and adjust for left and right boundaries
    if (adjustedPosition.x < 0) {
        adjustedPosition.x = 0;
        collision = true;
    }
    else if (adjustedPosition.x + objectSize.x > mapSize.x) {
        adjustedPosition.x = mapSize.x - objectSize.x;
        collision = true;
    }

    // Check and adjust for top and bottom boundaries
    if (adjustedPosition.y < 0) {
        adjustedPosition.y = 0;
        collision = true;
    }
    else if (adjustedPosition.y + objectSize.y > mapSize.y) {
        adjustedPosition.y = mapSize.y - objectSize.y;
        collision = true;
    }

    if (collision) {
        setPosition(adjustedPosition);
    }

    return collision;
}