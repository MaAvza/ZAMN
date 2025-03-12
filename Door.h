#pragma once
#include "StaticObject.h"

class Door : public StaticObject
{
public:
	Door();
	Door(sf::Texture* texture, sf::Vector2f position);
	~Door() {};

	void update(float deltaTime, const sf::Vector2f& mapSize) override {};
	void handleInput(sf::Event event, float dt) override {};

	bool isOpen() const;
	void setOpen(bool isOpen);

private:
	bool m_isOpen;
};