#include "Objects/StaticObjects/Weapon.h"

Weapon::Weapon()
	: StaticObject(),
	m_maxAmmo(100),
	m_ammo(0)
{
}

void Weapon::addAmmo(int amount)
{
	m_ammo = std::min(m_maxAmmo, m_ammo += amount);
}

int Weapon::getMaxAmmo() const
{
	return m_maxAmmo;
}

int Weapon::getAmmo() const
{
	return m_ammo;
}
