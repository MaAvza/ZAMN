#include "Objects/StaticObjects/CollectibleItem.h"

CollectibleItem::CollectibleItem()
	: StaticObject()
{
}

CollectibleItem::CollectibleItem(sf::Texture* texture, const sf::Vector2f& position)
	: StaticObject(texture, position)
{
}