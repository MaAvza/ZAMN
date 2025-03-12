#pragma once
#include "Weapon.h"
#include "Objects/MobileObjects/PelletGunProjectile.h"
#include "Utility/ResourceManager.h"

class PelletGun : public Weapon
{
public:
	PelletGun();
	PelletGun(sf::Texture* texture, const sf::Vector2f& position)
		:Weapon(texture, position),
		m_fireCooldown(0.5f),  // 0.5 seconds between shots
		m_currentCooldown(0.0f),
		m_isReloading(false),
		m_reloadTime(2.0f),    // 2 seconds to reload
		m_currentReloadTime(0.0f),
		m_magazineSize(10),    // 10 shots before needing to reload
		m_currentMagazine(m_magazineSize) {};

	~PelletGun() = default;

	void update(float deltaTime, const sf::Vector2f& mapSize) override;
	std::unique_ptr<Projectile> fire(const sf::Vector2f& startPosition, const sf::Vector2f& direction);

	void reload();
	bool isReloading() const;
	int getCurrentMagazine() const;
	int getMagazineSize() const;

	std::string getAmmoType() const override;
	std::string getName() const override;
private:
	float m_fireCooldown;
	float m_currentCooldown;
	bool m_isReloading;
	float m_reloadTime;
	float m_currentReloadTime;
	int m_magazineSize;
	int m_currentMagazine;
};