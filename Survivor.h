#pragma once
#include "MobileObject.h"

class Survivor : public MobileObject
{
public:
	Survivor(sf::Texture* texture, const sf::Vector2f& pos, Survivors::Type type);
	~Survivor() {};

	void update(float deltaTime, const sf::Vector2f& mapSize) override;
	void move(sf::Vector2f velocity, float dt) {};

	unsigned int getScore() const;
	unsigned int getHealth() const;

	void turnToZombie();
	void rescue();
	void reset();
	void takeDamage();

	void setScore(unsigned int score);
	void setHealth(unsigned int health);
	bool isRescued() const;
	bool isTurned() const;

private:
	unsigned int m_score;
	unsigned int m_health;
	
	Survivors::Type m_type;

	bool m_isRescued = false;
	bool m_isTurned = false;
};
