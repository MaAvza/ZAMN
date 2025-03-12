#include "Objects/MobileObjects/Zombie.h"
#include <Strategy/PatrolBehavior.h>

Zombie::Zombie()
	: Enemy()
{
}

Zombie::Zombie(sf::Texture* texture, const sf::Vector2f& position)
	: Enemy(texture, position)
{
}

Zombie::Zombie(const Zombie& other)
{
	m_behavior = std::make_unique<PatrolBehavior>(this, sf::Vector2f(0, 0));
	m_proxyCircle = other.m_proxyCircle;
	m_sprite = other.m_sprite;
	m_velocity = other.m_velocity;
	m_targetPosition = other.m_targetPosition;
}

std::unique_ptr<Enemy> Zombie::clone(const sf::Vector2f& position) const
{
	return std::make_unique<Zombie>(*this);
}

Enemies::Name Zombie::getType() const
{
	return Enemies::Name::Zombie;
}
