#include "GameManager.h"
#include <SFML/System.hpp>

GameManager::GameManager(sf::RenderWindow& window)
	: m_window(window), 
	m_projectileManager(),
	m_player(m_projectileManager)
{
	ResourceManager::getInstance()->loadResources();

	initLevel();

	sf::Vector2f spawnPos = m_map.getPlayerSpawnPosition();
	sf::Texture* idleTexture = ResourceManager::getInstance()->getTexture("idle");
	if (idleTexture) {
		m_player = Player(idleTexture, spawnPos, m_projectileManager);
	}

	addWeaponsToPlayerInventory();

	m_camera = Camera(sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y), m_map.getSize());
}

GameManager::~GameManager()
{
}

void GameManager::update(float deltaTime)
{
	processCommands(deltaTime);
	m_player.update(deltaTime, m_map.getSize());
	m_map.update(deltaTime);
	m_camera.update(m_player.getPosition());

	for (auto& object1 : m_map.getObjects())
	{
		for (auto& object2 : m_map.getObjects())
		{
			if (object1 != object2 && object1->getGlobalBounds().intersects(object2->getGlobalBounds()))
			{
				processCollision(*object1, *object2);
			}
		}
	}
	for (auto& object : m_map.getObjects())
	{
		if (m_player.getGlobalBounds().intersects(object->getGlobalBounds()))
		{
			processCollision(m_player, *object);
		}
	}
	for (auto& enemy : m_map.getEnemies())
	{
		if (m_player.getGlobalBounds().intersects(enemy->getGlobalBounds()))
		{
			processCollision(m_player, *enemy);
		}
	}
	updateEnemies(deltaTime);
	// Remove objects marked for deletion
	removeMarkedObjects();
	updateSurvivors();

	if (m_survivorsLeft == 0) {
		completeLevel();
	}

	if (m_player.getHealth() <= 0) {
		resetLevel();
	}
}

void GameManager::draw(sf::RenderWindow& window) const
{
	m_window.setView(m_camera.getView());
	m_map.draw(window);
	m_player.draw(window);
	window.draw(m_equippedItemText);
	window.draw(m_equippedWeaponText);
	window.draw(m_ammoText);
}

void GameManager::run()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
			handleInput(event);
		}

		float deltaTime = m_clock.restart().asSeconds();

		update(deltaTime);
		m_window.clear();
		draw(m_window);
		m_window.display();

		sf::sleep(sf::seconds(FRAME_TIME - deltaTime));
	}
}

void GameManager::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto it = m_player.getKeyMap().find(event.key.code);
		if (it != m_player.getKeyMap().end())
		{
			// Add a new command to the command queue based on the action mapped to the key
			std::unique_ptr<Command> command = createCommand(it->first);
			m_commandQueue.push(std::move(command));
		}
	}
}

void GameManager::processCommands(float deltaTime)
{
	while (!m_commandQueue.empty())
	{
		auto& command = m_commandQueue.front();
		command->execute(deltaTime);
		m_commandQueue.pop();
	}
}

std::unique_ptr<Command> GameManager::createCommand(sf::Keyboard::Key key)
{
	auto it = m_player.getKeyMap().find(key);
	if (it != m_player.getKeyMap().end())
	{
		Player::Action action = it->second;
		switch (action)
		{
		case Player::moveUp:
			return std::make_unique<MoveUpCommand>(m_player, action);
		case Player::moveLeft:
			return std::make_unique<MoveLeftCommand>(m_player, action);
		case Player::moveDown:
			return std::make_unique<MoveDownCommand>(m_player, action);
		case Player::moveRigth:
			return std::make_unique<MoveRightCommand>(m_player, action);
		case Player::changeItem:
			return std::make_unique<ChangeItemCommand>(m_player.getInventory(), action);
		case Player::changeWeapon:
			return std::make_unique<SwitchWeaponCommand>(m_player.getInventory(), action);
		case Player::useItem:
			return std::make_unique<UseItemCommand>(m_player.getInventory(), action);
		case Player::useWeapon:
			return std::make_unique<UseWeaponCommand>(m_player, action);
		default:
			return nullptr;
		}
	}
	return nullptr;
}

void GameManager::initLevel()
{
	std::string levelPath = "Level" + std::to_string(m_currentLevel) + ".tmx";
	std::cout << "Loading level " << levelPath << std::endl;

	if (!m_map.loadFromTmx(levelPath))
	{
		std::cerr << "Failed to load level " << std::to_string(m_currentLevel) << ".tmx" << std::endl;
		return;
	}

	m_camera.setMapSize(m_map.getSize());
	updateObstacleBounds();
	m_map.createEnemySamples();
}

void GameManager::resetLevel()
{
	m_player.reset();
	initLevel();
}

void GameManager::completeLevel()
{
	m_totalScore += m_levelScore;
	displayLevelCompleteMessage();
	loadNextLevel();
}

void GameManager::loadNextLevel()
{
	m_currentLevel++;
	initLevel();
}


bool GameManager::isMoveOutOfBounds(const sf::Vector2f& targetPosition)
{
	sf::Vector2f mapSize = m_map.getSize();
	
	if (targetPosition.x >= 0 && targetPosition.x <= mapSize.x &&
		targetPosition.y >= 0 && targetPosition.y <= mapSize.y)
		return true;
	
	return false;
}

void GameManager::updateObstacleBounds()
{
	m_obstacleBounds.clear();
	for (const auto& obj : m_map.getObjects())
	{
		auto obstacle = dynamic_cast<Obstacle*>(obj.get());
		if (obstacle)
		{
			m_obstacleBounds.push_back(obstacle->getGlobalBounds());
		}
	}
}

void GameManager::updateEnemies(float deltaTime)
{
	for (auto& enemy : m_map.getEnemies())
	{
		sf::Vector2f moveDirection = m_player.getPosition() - enemy->getPosition();

		if (isCollidingWithObstacles(enemy->getProxyCircle().getGlobalBounds()))
		{
			sf::Vector2f avoidanceVector = calculateAvoidanceVector(enemy->getPosition(), enemy->getProximityRadius());
			moveDirection += avoidanceVector;
			// Normalize direction
			float length = std::sqrt(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
			if (length > 0)
			{
				moveDirection /= length;
			}
		}

		enemy->move(moveDirection *ENEMY_SPEED, deltaTime);

		// Ensure the enemy stays within the map boundaries
		sf::Vector2f position = enemy->getPosition();
		sf::Vector2f mapSize = m_map.getSize();
		position.x = std::max(0.0f, std::min(position.x, mapSize.x));
		position.y = std::max(0.0f, std::min(position.y, mapSize.y));
		enemy->setPosition(position);
	}
}

void GameManager::updateSurvivors()
{
	m_survivorsLeft = 0;
	for (const auto& obj : m_map.getObjects())
	{
		auto survivor = dynamic_cast<Survivor*>(obj.get());
		if (survivor && !survivor->isRescued())
		{
			m_survivorsLeft++;
		}
	}
}

void GameManager::removeMarkedObjects()
{
	auto& objects = const_cast<Map::MapObjects&>(m_map.getObjects());
	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
			[](const auto& obj) {
				return obj->isMarkedForDeletion();
			}),
		objects.end());
}

bool GameManager::isCollidingWithObstacles(const sf::FloatRect& bounds) const
{
	for (const auto& obstacle : m_obstacleBounds)
	{
		if (bounds.intersects(obstacle))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2f GameManager::calculateAvoidanceVector(const sf::Vector2f& position, float radius) const
{
	sf::Vector2f avoidanceVector(0, 0);

	for (const auto& obstacle : m_obstacleBounds)
	{
		sf::Vector2f obstacleCenter(
			obstacle.left + obstacle.width / 2,
			obstacle.top + obstacle.height / 2
		);
		sf::Vector2f toObstacle = obstacleCenter - position;
		float distance = std::sqrt(toObstacle.x * toObstacle.x + toObstacle.y * toObstacle.y);

		if (distance < radius + std::max(obstacle.width, obstacle.height) / 2)
		{
			sf::Vector2f repulsion = position - obstacleCenter;
			float repulsionMagnitude = radius - distance;
			if (repulsionMagnitude > 0)
			{
				repulsion *= repulsionMagnitude / distance;
				avoidanceVector += repulsion;
			}
		}
	}

	return avoidanceVector;
}

void GameManager::displayLevelCompleteMessage() const
{
	sf::Text message;
	message.setFont(*ResourceManager::getInstance()->getFont("Scaryfeet")); 
	message.setString("Level Complete!\nScore: " + std::to_string(m_levelScore) + "\nTotal Score: " + std::to_string(m_totalScore));
	message.setCharacterSize(24);
	message.setFillColor(sf::Color::White);
	message.setPosition(m_window.getView().getCenter() - sf::Vector2f(100, 50));

	m_window.draw(message);
	m_window.display();

	sf::sleep(sf::seconds(5));
}

void GameManager::addWeaponsToPlayerInventory()
{
	std::shared_ptr<FlameThrower> flameThrower = std::make_shared<FlameThrower>(
		ResourceManager::getInstance()->getTexture("FlameThrower"),
		sf::Vector2f(0, 0)
	);
	std::shared_ptr<PelletGun> pelletGun = std::make_shared<PelletGun>(
		ResourceManager::getInstance()->getTexture("PelletGun"),
		sf::Vector2f(0, 0)
	);
	m_player.getInventory().addWeapon(flameThrower);
	m_player.getInventory().addWeapon(pelletGun);
}

void GameManager::initTextObjects()
{
	sf::Font* font = ResourceManager::getInstance()->getFont("Scaryfeet");
	if (font) {
		m_equippedItemText.setFont(*font);
		m_equippedItemText.setCharacterSize(24);
		m_equippedItemText.setFillColor(sf::Color::Magenta);
		m_equippedItemText.setOutlineColor(sf::Color::White);
		m_equippedItemText.setPosition(10, 10);

		m_equippedWeaponText.setFont(*font);
		m_equippedWeaponText.setCharacterSize(24);
		m_equippedWeaponText.setFillColor(sf::Color::Magenta);
		m_equippedWeaponText.setOutlineColor(sf::Color::White);
		m_equippedWeaponText.setPosition(10, 40);

		m_ammoText.setFont(*font);
		m_ammoText.setCharacterSize(24);
		m_ammoText.setFillColor(sf::Color::Magenta);
		m_ammoText.setOutlineColor(sf::Color::White);
		m_ammoText.setPosition(10, 70);
	}
}

void GameManager::updateTextObjects()
{
	sf::Vector2f viewCenter = m_camera.getView().getCenter();
	sf::Vector2f viewSize = m_camera.getView().getSize();

	// Set positions relative to the view center
	m_equippedItemText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 10);
	m_equippedWeaponText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 40);
	m_ammoText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 70);

	if (m_player.getInventory().getCurrentItem()) {
		m_equippedItemText.setString("Item: " + m_player.getInventory().getCurrentItem()->getName());
	}
	else {
		m_equippedItemText.setString("Item: None");
	}

	if (m_player.getInventory().getCurrentWeapon()) {
		m_equippedWeaponText.setString("Weapon: " + m_player.getInventory().getCurrentWeapon()->getName());
		m_ammoText.setString("Ammo: " + std::to_string(m_player.getInventory().getCurrentWeapon()->getAmmo()));
	}
	else {
		m_equippedWeaponText.setString("Weapon: None");
		m_ammoText.setString("Ammo: N/A");
	}
}
