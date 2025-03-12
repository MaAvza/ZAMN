#pragma once
#include "Enemy.h"

class TommyTheDoll : public Enemy
{
public:
	TommyTheDoll();
	TommyTheDoll(sf::Texture* texture, const sf::Vector2f& position);
	TommyTheDoll(const TommyTheDoll& other);

	~TommyTheDoll() = default;

	std::unique_ptr<Enemy> clone(const sf::Vector2f& position) const override;
	Enemies::Name getType() const override;

private:
};