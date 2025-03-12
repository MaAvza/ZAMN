#include "Objects/StaticObjects/StaticObject.h"

StaticObject::StaticObject()
	: GameObject()
{
}

StaticObject::StaticObject(sf::Texture* texture, const sf::Vector2f& position)
    : GameObject(texture, position)
{
    if (texture == nullptr)
    {
        m_shape.setSize(sf::Vector2f(10.f, 10.f));
        m_shape.setPosition(position);
        m_shape.setOrigin(5.f, 5.f);
    }
    else
    {
        sf::Vector2f size(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y));
        m_shape.setSize(size);
        m_sprite.setTexture(*texture);
    }
    m_shape.setPosition(position);
    m_sprite.setPosition(position);
    //m_shape.setOrigin(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);
    m_sprite.setOrigin(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);

    //set outline 
    m_shape.setOutlineThickness(1.f);
    m_shape.setFillColor(sf::Color::Transparent);
    m_shape.setOutlineColor(sf::Color::Red);
}

StaticObject::~StaticObject()
{
}

void StaticObject::setSize(const sf::Vector2f& size)
{
   
    if (m_texture != nullptr){
		m_sprite.setScale(size.x / m_texture->getSize().x,
			size.y / m_texture->getSize().y);
	}
	else
        m_shape.setSize(size);
}

sf::FloatRect StaticObject::getGlobalBounds() const
{
    if (m_texture != nullptr)
    {
        return m_sprite.getGlobalBounds();
    }
    else
    {
        return m_shape.getGlobalBounds();
    }

}

void StaticObject::draw(sf::RenderWindow& window) const
{
    if (m_sprite.getTexture() != nullptr)
		window.draw(m_sprite);
	//else
	   // window.draw(m_shape);
}

