#include "Strategy/PatrolBehavior.h"
#include "Objects/MobileObjects/Enemy.h"

PatrolBehavior::PatrolBehavior(Enemy* enemy, const sf::Vector2f& playerPosition)
	: m_enemy(enemy), m_targetPosition(playerPosition), m_state(State::Move), m_timer(0.0f)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	setRandomDirection();
}

PatrolBehavior::~PatrolBehavior()
{
}

void PatrolBehavior::execute(float dt)
{
	m_timer += dt;

	switch (m_state)
	{
	case State::Move:
		if (m_timer >= MOVE_DURATION)
		{
			m_state = State::Stop;
			m_timer = 0.0f;
		}
		else
		{
			m_enemy->move(m_direction, dt);
		}
		break;

	case State::Stop:
		if (m_timer >= STOP_DURATION)
		{
			m_state = State::Move;
			m_timer = 0.0f;
			setRandomDirection();
		}
		break;
	}
}

void PatrolBehavior::setRandomDirection()
{
	int directionIndex = std::rand() % 4;

	switch (directionIndex)
	{
	case 0:
		m_direction = sf::Vector2f(0, -1); // Up
		break;
	case 1:
		m_direction = sf::Vector2f(0, 1); // Down
		break;
	case 2:
		m_direction = sf::Vector2f(-1, 0); // Left
		break;
	case 3:
		m_direction = sf::Vector2f(1, 0); // Right
		break;
	}
}
