#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie();
	Zombie(sf::Texture* texture, const sf::Vector2f& position);
	Zombie(const Zombie& other);
	~Zombie() = default;

	std::unique_ptr<Enemy> clone(const sf::Vector2f& position) const override;
	Enemies::Name getType() const override;
};