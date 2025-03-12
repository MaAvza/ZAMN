#pragma once
#include "Objects/GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(sf::Texture* texture, const sf::Vector2f& position);
	~StaticObject();

	void update(float deltaTime, const sf::Vector2f& mapSize) override {};
	void handleInput(sf::Event event, float dt) override {};
	void setSize(const sf::Vector2f& size) override;
	sf::FloatRect getGlobalBounds() const;

	void draw(sf::RenderWindow& window) const;

private:
	sf::RectangleShape m_shape;
};