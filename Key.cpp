#include "Objects/StaticObjects/Key.h"
#include "Objects/MobileObjects/Player.h"

Key::Key()
	: CollectibleItem()
{
}

Key::Key(sf::Texture* texture, const sf::Vector2f& position)
	: CollectibleItem(texture, position)
{
}

void Key::onCollect(Player& player)
{
	player.getInventory().addItem(std::make_shared<Key>(*this));
}

bool Key::isConsumable() const
{
	return false;
}

std::string Key::getName() const
{
	return "Key";
}
