#pragma once
#include "Behavior.h"
#include <cstdlib>
#include <ctime>

class Enemy;

constexpr float MOVE_DURATION = 3.0f;
constexpr float STOP_DURATION = 1.0f;

class PatrolBehavior : public Behavior
{
public:
	PatrolBehavior(Enemy* enemy, const sf::Vector2f& playerPosition);
	~PatrolBehavior();

	void execute(float dt) override;

private:

	enum class State
	{
		Move,
		Stop
	};

	Enemy* m_enemy;
	State m_state;
	float m_timer;
	sf::Vector2f m_direction;
	sf::Vector2f m_targetPosition;

	void setRandomDirection();
};