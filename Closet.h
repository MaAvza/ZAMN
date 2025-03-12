#pragma once
#include "StaticObject.h"

class Closet : public StaticObject
{
public:
	Closet();
	Closet(sf::Texture* texture, sf::Vector2f position);
	~Closet() {};

	void update(float deltaTime, const sf::Vector2f& mapSize) override {};
	void handleInput(sf::Event event, float dt) override {};

	bool isOpen() const;
	void setOpen(bool isOpen);

private:
	bool m_isOpen;
};