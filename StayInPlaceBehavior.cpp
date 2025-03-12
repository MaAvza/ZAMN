#include "Strategy/StayInPlaceBehavior.h"

StayInPlaceBehavior::StayInPlaceBehavior(Enemy* enemy)
	: m_enemy(enemy)
{
}

StayInPlaceBehavior::~StayInPlaceBehavior()
{
	if (m_enemy)
	{
		delete m_enemy;
		m_enemy = nullptr;
	}
}

void StayInPlaceBehavior::execute(float dt)
{
}
