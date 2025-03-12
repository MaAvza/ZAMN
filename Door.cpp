#include "Objects/StaticObjects/Door.h"

Door::Door()
	: StaticObject(), m_isOpen(false)
{
}

Door::Door(sf::Texture* texture, sf::Vector2f position)
	: StaticObject(texture, position), m_isOpen(false)
{
}

bool Door::isOpen() const
{
	return m_isOpen;
}

void Door::setOpen(bool isOpen)
{
	m_isOpen = isOpen;
}

