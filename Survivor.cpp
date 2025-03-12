#include "Objects/MobileObjects/Survivor.h"

Survivor::Survivor(sf::Texture* texture, const sf::Vector2f& pos, Survivors::Type type)
	: MobileObject(texture, pos), m_score(Survivors::getScoreForType(type)), m_health(100), m_type(type)
{
}

void Survivor::update(float deltaTime, const sf::Vector2f& mapSize)
{
	if (m_health <= 0)
	{
		turnToZombie();
	}
}

unsigned int Survivor::getScore() const
{
	return m_score;
}

unsigned int Survivor::getHealth() const
{
	return m_health;
}

void Survivor::turnToZombie()
{
	m_type = Survivors::Type::TurnedZombie;
	m_score = Survivors::getScoreForType(m_type);
	m_isTurned = true;
}

void Survivor::rescue()
{
	m_isRescued = true;
}

void Survivor::reset()
{
	m_isRescued = false;
	m_isTurned = false;
}

void Survivor::takeDamage()
{
	if (m_health <= ZOMBIE_DAMAGE)
	{
		m_health = 0;
		m_isTurned = true;
	}
	else
	{
		m_health -= ZOMBIE_DAMAGE;
	}
}

void Survivor::setScore(unsigned int score)
{
	m_score = score;
}

void Survivor::setHealth(unsigned int health)
{
	m_health = health;
}

bool Survivor::isRescued() const
{
	return m_isRescued;
}

bool Survivor::isTurned() const
{
	return m_isTurned;
}
