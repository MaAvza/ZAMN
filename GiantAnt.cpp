#include "Objects/MobileObjects/GiantAnt.h"

GiantAnt::GiantAnt()
{
}

GiantAnt::GiantAnt(sf::Texture* texture, sf::Vector2f position)
	: Enemy(texture, position)
{
}

std::unique_ptr<Enemy> GiantAnt::clone(const sf::Vector2f& position) const
{
	return std::make_unique<GiantAnt>(*this);
}

Enemies::Name GiantAnt::getType() const
{
	return Enemies::Name::GiantAnt;
}

