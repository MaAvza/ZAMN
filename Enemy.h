#pragma once
#include "MobileObject.h"
#include "Utility/IPlayerObserver.h"
#include "Strategy/Behavior.h" 

const float ENEMY_SPEED = 70.0f;
const float ACCELERATION = 0.5f;
const float PROXIMITY_RADIUS = 50.0f;

class Enemy : public MobileObject, public IPlayerObserver
{
public:
	Enemy();
	Enemy(const Enemy& other);
	Enemy(sf::Texture* texture, const sf::Vector2f& position);
	virtual ~Enemy() = default;

	void update(float deltaTime, const sf::Vector2f& mapSize);
	void move(sf::Vector2f velocity, float dt);
	virtual std::unique_ptr<Enemy> clone(const sf::Vector2f& position) const = 0;

	void setBehavior(std::unique_ptr<Behavior> newBehavior);
	void onPlayerPositionUpdate(const sf::Vector2f& playerPosition) override;
	void draw(sf::RenderWindow& window) const override;

	const sf::CircleShape& getProxyCircle() const;
	const float getProximityRadius() const;
	float getDamageAtContact() const;

	virtual Enemies::Name getType() const = 0;

protected:
	std::unique_ptr<Behavior> m_behavior;
	sf::CircleShape m_proxyCircle; 
	float m_damageAtContact = 17.0f;

	bool isTargetWithinProximity() const;
};