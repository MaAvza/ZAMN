#pragma once
#include "CollectibleItem.h"

class FirstAidKit : public CollectibleItem
{
public:
	FirstAidKit();
	FirstAidKit(sf::Texture* texture, const sf::Vector2f& position);
	~FirstAidKit() = default;

	void onCollect(class Player& player);
	bool isConsumable() const;
	std::string getName() const;
};