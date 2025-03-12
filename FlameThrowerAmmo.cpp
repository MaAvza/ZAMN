#include "Objects/StaticObjects/FlameThrowerAmmo.h"
#include "Objects/MobileObjects/Player.h"

FlameThrowerAmmo::FlameThrowerAmmo()
	:CollectibleItem(), m_quantity(10)
{
}

FlameThrowerAmmo::FlameThrowerAmmo(sf::Texture* texture, const sf::Vector2f& position, const int& quantity)
	:CollectibleItem(texture, position), m_quantity(quantity)
{
}

void FlameThrowerAmmo::onCollect(Player& player)
{
	player.getInventory().addItem(std::make_shared<FlameThrowerAmmo>(m_texture, sf::Vector2f(0, 0), m_quantity));
}

bool FlameThrowerAmmo::isConsumable() const
{
	return true;
}

std::string FlameThrowerAmmo::getName() const
{
	return "FlameThrowerAmmo";
}
