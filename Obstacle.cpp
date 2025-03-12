#include "Objects/StaticObjects/Obstacle.h"

Obstacle::Obstacle()
	: StaticObject()
{
}

Obstacle::Obstacle(sf::Texture* texture, sf::Vector2f position)
	: StaticObject(texture, position)
{
}
