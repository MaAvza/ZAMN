#pragma once
#include "MobileObject.h"
#include <unordered_map>
#include <functional>
#include <iostream>
#include "Objects/Inventory.h"
#include "Utility/IPlayerObserver.h"
#include "Utility/ProjectileManager.h"

const float PLAYER_SPEED = 400.0f;
const float DRAGGING_DURATION = 2.0f;

class Player : public MobileObject
{
public:

	enum MissionStatus
	{
		missionInProgress,
		missionCompleted,
		missionFailed
	};

	enum Action
	{
		moveRigth, // D
		moveLeft, // A
		moveUp, // W
		moveDown, // S
		useWeapon, // Space
		changeWeapon, // C
		useItem, // V
		changeItem, // B
		radarOnOff // ~
	};

	Player(ProjectileManager& projectileManager);
	Player(sf::Texture* texture, sf::Vector2f position, ProjectileManager& projectileManager);
	~Player() {};
	
	Player(Player&& other) noexcept; // Move constructor
	Player& operator=(Player&& other) noexcept; // Move assignment operator
	
	// Delete copy constructor and copy assignment operator
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;

	void update(float deltaTime, const sf::Vector2f& mapSize) override;
	void draw(sf::RenderWindow& window) const;
	void handleInput(sf::Event event, float dt);

	void move(sf::Vector2f velocity, float dt) override; 
	const std::map<sf::Keyboard::Key, Action>& getKeyMap() const;

	/*===========================*/
	/* inventory related methods */
	/*===========================*/
	bool fireWeapon();
	std::shared_ptr<Weapon> getEquippedWeapon() const;
	const Inventory& getInventory() const;
	Inventory& getInventory();

	/*===========================*/
	/*		observers setup		 */
	/*===========================*/
	void registerObserver(IPlayerObserver* observer);
	void removeObserver(IPlayerObserver* observer);
	void notifyObservers();

	void startDragging();
	void updateDragging(float deltaTime);
	void addScore(int score);
	void reset();

private:
	unsigned int m_score;
	Inventory m_inventory;
	bool m_isBeingDragged = false;
	float m_draggingTime = 0.0f;
	ProjectileManager& m_projectileManager;

	std::vector<std::shared_ptr<IPlayerObserver>> m_observers;
	std::map<sf::Keyboard::Key, Action> m_keyMap;
	MissionStatus m_missionStatus;
	void initKeyMap();
};