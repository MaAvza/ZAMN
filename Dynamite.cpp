#include "Objects/StaticObjects/Dynamite.h"
#include "Objects/MobileObjects/Player.h"

Dynamite::Dynamite()
	: CollectibleItem()
{
}

Dynamite::Dynamite(sf::Texture* texture, const sf::Vector2f& position)
	: CollectibleItem(texture, position)
{
}

void Dynamite::onCollect(Player& player)
{
	player.getInventory().addItem(std::make_shared<Dynamite>(*this));
}

bool Dynamite::isConsumable() const
{
	return true;
}

std::string Dynamite::getName() const
{
	return "Dynamite";
}
