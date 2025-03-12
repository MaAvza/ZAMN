#pragma once
#include "StaticObject.h"
#include "Objects/MobileObjects/Projectile.h"

class Weapon : public StaticObject
{
public:
    Weapon();
    Weapon(sf::Texture* texture, const sf::Vector2f& position)
		:StaticObject(texture, position),
		m_maxAmmo(100),
		m_ammo(0) {}

    virtual ~Weapon() = default;

    virtual void update(float deltaTime, const sf::Vector2f& mapSize) = 0;
    virtual std::unique_ptr<Projectile> fire(const sf::Vector2f& startPosition, const sf::Vector2f& direction) = 0;

    virtual std::string getAmmoType() const = 0;

    void addAmmo(int amount);
    int getMaxAmmo() const;
    int getAmmo() const;
    virtual std::string getName() const = 0;
protected:
    int m_maxAmmo;
	int m_ammo;
};