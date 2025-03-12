#pragma once
#include "CollectibleItem.h"

class FlameThrowerAmmo : public CollectibleItem
{
public:
	FlameThrowerAmmo();
	FlameThrowerAmmo(sf::Texture* texture, const sf::Vector2f& position, const int& quantity = 10);
	~FlameThrowerAmmo() {};

	void onCollect(Player& player) override;
	bool isConsumable() const override;
	std::string getName() const override;
private:
	int m_quantity;
};