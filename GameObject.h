#pragma once
#include "Utility/Globals.h"

class GameObject
{
public:
	GameObject();
	GameObject(sf::Texture* texture, const sf::Vector2f& position);
	virtual ~GameObject() {};

	virtual void update(float deltaTime, const sf::Vector2f& mapSize) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual void handleInput(sf::Event event, float dt) = 0;
	virtual void setSize(const sf::Vector2f& size);

	void markForDeletion();
	bool isMarkedForDeletion() const;
	virtual sf::FloatRect getGlobalBounds() const;

protected:
	sf::Texture* m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_lastKnownDirection;
	bool m_isMarkedForDeletion;
};