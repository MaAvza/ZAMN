#pragma once
#include "CollectibleItem.h"

class Dynamite : public CollectibleItem
{
public:
	Dynamite();
	Dynamite(sf::Texture* texture, const sf::Vector2f& position);
	~Dynamite() = default;

	void onCollect(Player& player) override;
	bool isConsumable() const override;
	std::string getName() const override;
};