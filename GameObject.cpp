#include "Objects/GameObject.h"	

GameObject::GameObject() :
	m_position(0, 0), m_texture(nullptr), m_sprite(sf::Sprite()), m_size(0, 0), m_isMarkedForDeletion(false),
    m_lastKnownDirection(0, 0)
{
}

GameObject::GameObject(sf::Texture* texture, const sf::Vector2f& position)
{
    sf::Vector2f desiredSize(34, 34);
    m_position = position;
    if (texture == nullptr)
    {
        m_texture = nullptr;
        m_sprite = sf::Sprite();
        m_size = sf::Vector2f(0, 0);
        m_sprite.setPosition(m_position);
    }
    else
    {
        m_texture = texture;
        m_sprite.setTexture(*m_texture);
        m_sprite.setPosition(m_position);

        // Calculate the scale factor
        sf::Vector2f textureSize(m_texture->getSize());
        float scaleX = desiredSize.x / textureSize.x;
        float scaleY = desiredSize.y / textureSize.y;

        // Use the smaller scale to maintain aspect ratio
        float scale = std::min(scaleX, scaleY);

        // Set the sprite scale
        m_sprite.setScale(scale, scale);

        // Calculate the actual size after scaling
        m_size = sf::Vector2f(textureSize.x * scale, textureSize.y * scale);
        m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
    }
    m_isMarkedForDeletion = false;
    m_lastKnownDirection = sf::Vector2f(0, 0);
}

void GameObject::setSize(const sf::Vector2f& size)
{
	m_size = size;
	if (m_texture == nullptr)
	{
		m_sprite.setScale(m_size.x, m_size.y);
	}
	else
		m_sprite.setScale(m_size.x / m_texture->getSize().x, m_size.y / m_texture->getSize().y);
}

void GameObject::markForDeletion()
{
	m_isMarkedForDeletion = true;
}

bool GameObject::isMarkedForDeletion() const
{
    return m_isMarkedForDeletion;
}

sf::FloatRect GameObject::getGlobalBounds() const
{
    if (m_sprite.getTexture() != nullptr)
    {
        return m_sprite.getGlobalBounds();
    }
    else
    {
        float left = m_position.x - (m_size.x / 2.0f);
        float top = m_position.y - (m_size.y / 2.0f);
        return sf::FloatRect(left, top, m_size.x, m_size.y);
    }
}
