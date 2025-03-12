 Zombies Ate My Neighbors Clone
=======================================
This project is a C++ implementation of a game inspired by the classic "Zombies Ate My Neighbors". It's a top-down shooter where players navigate through various levels, fighting off zombies and other monsters while trying to rescue survivors.

=======================================
- Top-down 2D gameplay
- Multiple enemy types (Zombies, Giant Ants, Tommy the Doll)
- Procedural enemy spawning
- Collectible items and weapons
- Level-based progression
- SFML graphics library for rendering

Dependencies
======================================
- TinyXML2 (for parsing level files)

Header Files and Functions
======================================
GameManager.h
The central class managing the game state and main loop.

Notable functions:
- `update(float deltaTime)`: Updates game state, including player, enemies, and collisions.
- `draw(sf::RenderWindow& window)`: Renders all game objects to the screen.
- `handleInput(sf::Event event)`: Processes user input.

Map.h
Manages the game level, including obstacles, items, and enemy spawning.

Notable functions:
- `loadFromTmx(const std::string& tmxFile)`: Loads level data from a TMX file.
- `spawnEnemies()`: Creates new enemies at random positions.
- `update(float deltaTime)`: Updates all objects on the map.

Player.h
Represents the player character.

Notable functions:
- `move(const sf::Vector2f& direction)`: Moves the player.
- `useWeapon()`: Activates the current weapon.
- `collectItem(Item* item)`: Adds an item to the player's inventory.

Enemy.h
Base class for all enemy types.

Notable functions:
- `update(float deltaTime)`: Updates enemy behavior and position.
- `takeDamage(int amount)`: Reduces enemy health and checks for defeat.

GameObject.h
Base class for all game objects (players, enemies, items, etc.).

Notable functions:
- `getPosition()`: Returns the object's current position.
- `setPosition(const sf::Vector2f& pos)`: Sets the object's position.
- `getGlobalBounds()`: Returns the object's bounding box for collision detection.

CollisionHandler.h
Manages collision detection and resolution between game objects.

Notable functions:
- `checkCollisions(GameObject& obj1, GameObject& obj2)`: Detects collisions between two objects.
- `resolveCollision(GameObject& obj1, GameObject& obj2)`: Handles the outcome of a collision.

ResourceManager.h
Singleton class managing game resources like textures and sounds.

Notable functions:
- `getTexture(const std::string& name)`: Retrieves a texture by name.
- `loadResources()`: Loads all game resources into memory.

EnemySpawner.h
Handles the creation and placement of enemies in the game.

Notable functions:
- `spawnEnemies(Enemies::Name enemyName, const sf::Vector2f& mapSize, int minEnemies, int maxEnemies)`: Creates a group of enemies of a specific type.
- `registerEnemyCreator(Enemies::Name name, EnemyCreator creator)`: Registers a function to create a specific enemy type.

Inventory.h
Manages the player's collected items and weapons.

Notable functions:
- `addItem(std::unique_ptr<Item> item)`: Adds an item to the inventory.
- `useItem(ItemType type)`: Uses an item from the inventory.
- `switchWeapon()`: Changes the currently equipped weapon.

Current Known Issues and Future Improvements
=============================================
Enemy Spawning and Balancing
There is currently an issue with enemy spawning that results in an overwhelming number of enemies appearing on the map. This leads to two main problems:

1. Performance issues due to too many entities being updated and rendered simultaneously.
2. Gameplay imbalance where survivors (victims) are killed almost immediately, making the game extremely difficult.

Planned fixes and improvements
===============================
1. **Adjust Spawn Rates**: Modify the `MIN_ENEMIES` and `MAX_ENEMIES` constants in `Map.h` to reduce the number of enemies spawned at once.

2. **Implement Spawn Cooldown**: Add a cooldown period between enemy spawns to prevent sudden surges of enemies.

3. **Dynamic Difficulty Adjustment**: Implement a system that adjusts enemy spawn rates based on the player's performance and current game state.

4. **Safe Zones for Survivors**: Create areas on the map where survivors are temporarily protected from enemies, giving players a chance to rescue them.

5. **Enemy Behavior Tuning**: Adjust enemy movement speeds and attack patterns to make the game challenging but fair.

6. **Limit Active Enemies**: Implement a cap on the total number of active enemies on the map at any given time.

To-Do List for Fixing These Issues:

1. In `Map.h`, reduce `MIN_ENEMIES` and `MAX_ENEMIES` values.
2. Implement a spawn cooldown in `Map::spawnEnemies()`:
   ```cpp
   if (m_spawnClock.getElapsedTime().asSeconds() >= SPAWN_COOLDOWN) {
       // Spawn enemies
       m_spawnClock.restart();
   }
