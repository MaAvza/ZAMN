#pragma once
#include "SFML/Graphics.hpp"
#include "Utility/ResourceManager.h"
#include "Commands/MoveDownCommand.h"
#include "Commands/MoveLeftCommand.h"
#include "Commands/MoveRightCommand.h"
#include "Commands/MoveUpCommand.h"
#include "Commands/ChangeItemCommand.h"
#include "Commands/SwitchWeaponCommand.h"
#include "Commands/UseItemCommand.h"
#include "Commands/UseWeaponCommand.h"
#include "Objects/CollisionHandler.h"
#include "Utility/Map.h"
#include "Utility/Camera.h"
#include <queue>
#include <cmath>

class GameManager
{
public:
    GameManager(sf::RenderWindow& window);
    ~GameManager();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void run();

    void handleInput(sf::Event event);

private:
    ProjectileManager m_projectileManager;
    sf::RenderWindow& m_window;
    sf::Clock m_clock;
    Camera m_camera;
    Player m_player;
    Map m_map;

    unsigned int m_currentLevel = 1;
    unsigned int m_levelScore = 0;
    unsigned int m_totalScore = 0;
    unsigned int m_survivorsLeft = 0;

    sf::Text m_equippedItemText;
    sf::Text m_equippedWeaponText;
    sf::Text m_ammoText;

    std::queue<std::unique_ptr<Command>> m_commandQueue;
    std::vector<sf::FloatRect> m_obstacleBounds;

    void processCommands(float deltaTime);
    std::unique_ptr<Command> createCommand(sf::Keyboard::Key key);

    void initLevel();
    void resetLevel();
    void completeLevel();
    void loadNextLevel();

    bool isMoveOutOfBounds(const sf::Vector2f& targetPosition);

    void updateObstacleBounds();
    void updateEnemies(float deltaTime);
    void updateSurvivors();
    void removeMarkedObjects();

    bool isCollidingWithObstacles(const sf::FloatRect& bounds) const;
    sf::Vector2f calculateAvoidanceVector(const sf::Vector2f& position, float radius) const;

    void displayLevelCompleteMessage() const;
    void addWeaponsToPlayerInventory();
    void initTextObjects();
    void updateTextObjects();
};
