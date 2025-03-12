#pragma once
#include "Behavior.h"

class Enemy;

class ChaseBehavior : public Behavior
{
public:
	ChaseBehavior(Enemy* enemy, const sf::Vector2f& playerPosition);
	~ChaseBehavior() = default;

	void execute(float dt) override;
private:
	Enemy* m_enemy;
	sf::Vector2f m_targetPosition;
};