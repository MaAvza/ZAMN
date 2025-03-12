#pragma once
#include "Enemy.h"

class GiantAnt : public Enemy
{
public:
	GiantAnt();
	GiantAnt(sf::Texture* texture, sf::Vector2f position);
	~GiantAnt() = default;

	std::unique_ptr<Enemy> clone(const sf::Vector2f& position) const;
	Enemies::Name getType() const override;
};