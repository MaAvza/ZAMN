#include "Strategy/ChaseBehavior.h"
#include "Objects/MobileObjects/Enemy.h"

ChaseBehavior::ChaseBehavior(Enemy* enemy, const sf::Vector2f& playerPosition)
	: m_enemy(enemy)
	, m_targetPosition(playerPosition)
{
}

void ChaseBehavior::execute(float dt)
{
	sf::Vector2f direction = m_targetPosition - m_enemy->getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length;

	m_enemy->move(direction, dt);
}
