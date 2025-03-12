#include "Objects/MobileObjects/TommyTheDoll.h"
#include "Strategy/ChaseBehavior.h"

TommyTheDoll::TommyTheDoll()
	: Enemy()
{
}

TommyTheDoll::TommyTheDoll(sf::Texture* texture, const sf::Vector2f& position)
	: Enemy(texture, position)
{
	setBehavior(std::make_unique<ChaseBehavior>(this, sf::Vector2f(0, 0)));
}

TommyTheDoll::TommyTheDoll(const TommyTheDoll& other)
	: Enemy(other)
{
	setBehavior(std::make_unique<ChaseBehavior>(this, sf::Vector2f(0, 0)));
}

std::unique_ptr<Enemy> TommyTheDoll::clone(const sf::Vector2f& position) const
{
	return std::make_unique<TommyTheDoll>(*this);
}

Enemies::Name TommyTheDoll::getType() const
{
	return Enemies::Name::TommyTheDoll;
}
