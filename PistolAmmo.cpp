#include "Objects/StaticObjects/PistolAmmo.h"
#include "Objects/MobileObjects/Player.h"

PistolAmmo::PistolAmmo()
	:CollectibleItem(),
	m_quantity(10)
{
}

PistolAmmo::PistolAmmo(sf::Texture* texture, const sf::Vector2f& position, const int& quantity)
	:CollectibleItem(texture, position),
	m_quantity(quantity)
{
}

void PistolAmmo::onCollect(Player& player)
{
	player.getInventory().addItem(std::make_shared<PistolAmmo>(*this));
}

bool PistolAmmo::isConsumable() const
{
	return true;
}

std::string PistolAmmo::getName() const
{
	return "PistolAmmo";
}
