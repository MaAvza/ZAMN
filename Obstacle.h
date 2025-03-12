#pragma once
#include "StaticObject.h"

class Obstacle : public StaticObject
{
public:
	Obstacle();
	Obstacle(sf::Texture* texture, sf::Vector2f position);
	~Obstacle() {};

	void update(float deltaTime, const sf::Vector2f& mapSize) override {};
	void handleInput(sf::Event event, float dt) override {};

};