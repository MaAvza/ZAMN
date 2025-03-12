#pragma once
#include "CollectibleItem.h"

class PistolAmmo : public CollectibleItem
{
public:
	PistolAmmo();
	PistolAmmo(sf::Texture* texture, const sf::Vector2f& position, const int& quantity = 10);
	~PistolAmmo() = default;

	void onCollect(Player& player) override;
	bool isConsumable() const override;
	std::string getName() const override;

private:
	int m_quantity;
};