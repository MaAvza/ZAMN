#include "Objects/StaticObjects/Closet.h"

Closet::Closet()
	: m_isOpen(false)
{
}

Closet::Closet(sf::Texture* texture, sf::Vector2f position)
	: StaticObject(texture, position), m_isOpen(false)
{
}

bool Closet::isOpen() const
{
	return m_isOpen;
}

void Closet::setOpen(bool isOpen)
{
	m_isOpen = isOpen;
}