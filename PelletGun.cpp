#include "Objects/StaticObjects/PelletGun.h"

PelletGun::PelletGun()
	: Weapon(ResourceManager::getInstance()->getTexture("PelletGun"), sf::Vector2f(0, 0)),
	m_fireCooldown(0.5f),
	m_currentCooldown(0.0f),
	m_isReloading(false),
	m_reloadTime(2.0f),
	m_currentReloadTime(0.0f),
	m_magazineSize(10),
	m_currentMagazine(m_magazineSize)
{
	m_ammo = 100;
}

void PelletGun::update(float deltaTime, const sf::Vector2f& mapSize)
{
    if (m_currentCooldown > 0) {
        m_currentCooldown -= deltaTime;
        if (m_currentCooldown < 0) m_currentCooldown = 0;
    }

    if (m_isReloading) {
        m_currentReloadTime += deltaTime;
        if (m_currentReloadTime >= m_reloadTime) {
            m_isReloading = false;
            m_currentReloadTime = 0;
            m_currentMagazine = std::min(m_magazineSize, m_ammo);
            m_ammo -= m_currentMagazine;
        }
    }
}

std::unique_ptr<Projectile> PelletGun::fire(const sf::Vector2f& startPosition, const sf::Vector2f& direction)
{
	if (m_ammo > 0)
	{
		m_ammo--;
		return std::make_unique<PelletGunProjectile>(ResourceManager::getInstance()->getTexture("Bullet"), 
			startPosition, 
			direction,
			PELLET_BULLET_SPEED,
			PELLET_BULLET_DAMAGE,
			PELLET_BULLET_MAX_DISTANCE);
	}
	return nullptr;
}

void PelletGun::reload()
{
    if (!m_isReloading && m_currentMagazine < m_magazineSize && m_ammo > 0) 
    {
        m_isReloading = true;
        m_currentReloadTime = 0;
    }
}

bool PelletGun::isReloading() const
{
    return m_isReloading;
}

int PelletGun::getCurrentMagazine() const
{
    return m_currentMagazine;
}

int PelletGun::getMagazineSize() const
{
    return m_magazineSize;
}

std::string PelletGun::getAmmoType() const
{
    return "PistolAmmo";
}

std::string PelletGun::getName() const
{
    return "PelletGun";
}
