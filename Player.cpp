#include "Objects/MobileObjects/Player.h"
#include <Objects/StaticObjects/PistolAmmo.h>
#include <Objects/StaticObjects/FlameThrowerAmmo.h>

Player::Player(ProjectileManager& projectileManager)
	: MobileObject(), m_score(0), m_missionStatus(missionInProgress),
	m_projectileManager(projectileManager)
{
	initKeyMap();
}

Player::Player(sf::Texture* texture, sf::Vector2f position, ProjectileManager& projectileManager) :
	MobileObject(texture, position), m_score(0), m_missionStatus(missionInProgress),
	m_projectileManager(projectileManager)
{
	initKeyMap();
}

Player::Player(Player&& other) noexcept
	: MobileObject(std::move(other)), // Move base class
	m_score(other.m_score),
	m_inventory(std::move(other.m_inventory)),
	m_projectileManager(other.m_projectileManager), // Transfer reference
	m_observers(std::move(other.m_observers)),
	m_keyMap(std::move(other.m_keyMap)),
	m_missionStatus(other.m_missionStatus)
{
	// Reset the source object's members if necessary
	other.m_score = 0;
	other.m_health = 0.0f;
	other.m_missionStatus = missionInProgress;
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other)
	{
		MobileObject::operator=(std::move(other)); // Move base class

		m_score = other.m_score;
		m_inventory = std::move(other.m_inventory);
		m_health = other.m_health;
		m_projectileManager = std::move(other.m_projectileManager); // Move reference
		m_observers = std::move(other.m_observers);
		m_keyMap = std::move(other.m_keyMap);
		m_missionStatus = other.m_missionStatus;

		// Reset the source object's members
		other.m_score = 0;
		other.m_health = 0.0f;
		other.m_missionStatus = missionInProgress;
	}
	return *this;
}

void Player::update(float deltaTime, const sf::Vector2f& mapSize)
{
	MobileObject::update(deltaTime, mapSize);

	if (m_velocity != sf::Vector2f(0, 0))
		notifyObservers();
	
	if (std::abs(m_velocity.x) > 0.1f || std::abs(m_velocity.y) > 0.1f)
	{
		float magnitude = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		m_lastKnownDirection = m_velocity / magnitude;
	}
}

void Player::draw(sf::RenderWindow& window) const
{
	sf::CircleShape positionMarker(5);
	positionMarker.setFillColor(sf::Color::Magenta);
	positionMarker.setPosition(m_sprite.getPosition());
	window.draw(positionMarker);
	window.draw(m_sprite);
}

void Player::handleInput(sf::Event event, float dt)
{
}

void Player::move(sf::Vector2f velocity, float dt)
{
	dt = std::max(dt, MIN_DELTA_TIME);
	m_velocity = velocity;
	m_targetPosition += velocity * dt * PLAYER_SPEED;
}

const std::map<sf::Keyboard::Key, Player::Action>& Player::getKeyMap() const
{
	return m_keyMap;
}

/*==============================================================================*/
/*						  observers related functions				    		*/	
/*==============================================================================*/
void Player::registerObserver(IPlayerObserver* observer)
{
	m_observers.emplace_back(std::shared_ptr<IPlayerObserver>(observer));
}

void Player::removeObserver(IPlayerObserver* observer)
{
	auto it = std::find_if(m_observers.begin(), m_observers.end(), 
		[&](const std::shared_ptr<IPlayerObserver>& o) {
		return o.get() == observer;
	});

	if (it != m_observers.end())
	{
		m_observers.erase(it);
	}
}

void Player::notifyObservers()
{
	for (auto& observer : m_observers)
	{
		observer->onPlayerPositionUpdate(m_sprite.getPosition());
	}

}
/*==============================================================================*/

void Player::startDragging()
{
	m_isBeingDragged = true;
	m_draggingTime = 0.0f;
}

void Player::updateDragging(float deltaTime)
{
	if (m_isBeingDragged)
	{
		m_draggingTime += deltaTime;
		if (m_draggingTime >= DRAGGING_DURATION)
		{
			m_isBeingDragged = false;
			m_draggingTime = 0.0f;
		}
	}
}

void Player::addScore(int score)
{
	m_score += score;
}

void Player::reset()
{
	m_score = 0;
	m_health = 100.0f;
	m_missionStatus = missionInProgress;
}

bool Player::fireWeapon()
{
	if (m_inventory.getCurrentWeapon())
	{
		auto projectile = m_inventory.getCurrentWeapon()->fire(m_position, m_lastKnownDirection);
		m_projectileManager.addProjectile(std::move(projectile));
		return true;
	}
	return false;
}

std::shared_ptr<Weapon> Player::getEquippedWeapon() const
{
	return m_inventory.getCurrentWeapon();
}

const Inventory& Player::getInventory() const
{
	return m_inventory;
}

Inventory& Player::getInventory()
{
	return m_inventory;
}

void Player::initKeyMap()
{
	m_keyMap[sf::Keyboard::D] = moveRigth;
	m_keyMap[sf::Keyboard::A] = moveLeft;
	m_keyMap[sf::Keyboard::W] = moveUp;
	m_keyMap[sf::Keyboard::S] = moveDown;
	m_keyMap[sf::Keyboard::C] = changeWeapon;
	m_keyMap[sf::Keyboard::V] = useItem;
	m_keyMap[sf::Keyboard::B] = changeItem;
	m_keyMap[sf::Keyboard::Space] = useWeapon;
	//m_keyMap[sf::Keyboard::Tilde] = radarOnOff;
}


