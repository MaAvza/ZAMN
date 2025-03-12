#include "Objects/StaticObjects/FirstAidKit.h"
#include "Objects/MobileObjects/Player.h"

FirstAidKit::FirstAidKit()
	: CollectibleItem()
{
}

FirstAidKit::FirstAidKit(sf::Texture* texture, const sf::Vector2f& position)
	: CollectibleItem(texture, position)
{
}

void FirstAidKit::onCollect(Player& player)
{
	player.setHealth(PLAYER_MAX_HEALTH);
}

bool FirstAidKit::isConsumable() const
{
	return true;
}

std::string FirstAidKit::getName() const
{
	return "FirstAidKit";
}
