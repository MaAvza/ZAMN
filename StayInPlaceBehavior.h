#pragma once
#include "Behavior.h"

class Enemy;

class StayInPlaceBehavior : public Behavior
{
public:
	StayInPlaceBehavior(Enemy* enemy);
	~StayInPlaceBehavior();

	void execute(float dt) override;

private:
	Enemy* m_enemy;
};