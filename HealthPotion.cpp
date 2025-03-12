#include "Objects/StaticObjects/HealthPotion.h"
#include "Objects/MobileObjects/Player.h"

HealthPotion::HealthPotion()
	: CollectibleItem()
{
}

HealthPotion::HealthPotion(sf::Texture* texture, const sf::Vector2f& position)
	: CollectibleItem(texture, position)
{
}

void HealthPotion::onCollect(Player& player)
{
	player.setHealth(player.getHealth()*HEAL_RATE + player.getHealth());
}

bool HealthPotion::isConsumable() const
{
	return true;
}

std::string HealthPotion::getName() const
{
	return "HealthPotion";
}
