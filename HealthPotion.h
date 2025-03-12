#pragma once
#include "CollectibleItem.h"

class HealthPotion : public CollectibleItem
{
public:
	HealthPotion();
	HealthPotion(sf::Texture* texture, const sf::Vector2f& position);
	~HealthPotion() = default;

	void onCollect(class Player& player);
	bool isConsumable() const;
	std::string getName() const;
};