#pragma once
#include "CollectibleItem.h"

class Key : public CollectibleItem
{
public:
	Key();
	Key(sf::Texture* texture, const sf::Vector2f& position);
	~Key() = default;

	void onCollect(Player& player) override;
	bool isConsumable() const override;
	std::string getName() const override;
};