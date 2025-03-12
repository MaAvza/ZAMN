#pragma once
#include "Objects/GameObject.h"

class MobileObject : public GameObject
{
public:
	MobileObject();
	MobileObject(sf::Texture* texture, const sf::Vector2f& position);
	~MobileObject();

    void update(float deltaTime, const sf::Vector2f& mapSize);
	void draw(sf::RenderWindow& window) const;
	void handleInput(sf::Event event, float dt);

	virtual void move(sf::Vector2f velocity, float dt) = 0; 

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	void setVelocity(sf::Vector2f velocity);
	const sf::Vector2f& getVelocity() const;
	void hit(float damage);
	float getHealth() const;
	void setHealth(float health);

protected:
	sf::Vector2f m_velocity;
	sf::Vector2f m_targetPosition;
	float m_health;

	bool checkAndHandleBoundaryCollision(const sf::Vector2f& newPosition, const sf::Vector2f& mapSize);
};