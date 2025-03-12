#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>

const sf::Vector2f WINDOW_SIZE(800, 600);
const sf::Vector2f CENTER(400, 300);

const float MOVE_SPEED = 0.1f;
const float ZOOM_SPEED = 0.1f;
const float HEAL_RATE = 0.7f;
const float PLAYER_MAX_HEALTH = 100.0f;
const float MIN_ZOOM = 0.5f;
const float MAX_ZOOM = 2.0f;
const float FRAME_TIME = 1.0f / 60.0f;
const float PIXEL_TO_METER = 100.0f;
const float MIN_DELTA_TIME = 0.01f;
const float SPAWN_INTERVAL = 3.0f;
const int ZOMBIE_DAMAGE = 10;
const int MIN_ENEMIES = 1;
const int MAX_ENEMIES = 4;
const int MAX_LEVEL = 1;
const int ENEMY_TYPES = 4;
const size_t MAX_WEAPONS = 2;
const size_t MAX_ITEMS = 6;
const float PELLET_BULLET_SPEED = 500.0f;
const float PELLET_BULLET_DAMAGE = 30.0f;
const float PELLET_BULLET_MAX_DISTANCE = 200.0f;

namespace Survivors
{
	enum Type
	{
		Man = 10,
		Baby = 25,
		Puppy = 3,
		Tourists = 12,
		Teacher = 1,
		Cheerleader = 15,
		TurnedZombie = 0
	};

	inline int getScoreForType(Type type)
	{
		return static_cast<int>(type);
	}
}

namespace Pickups
{
	enum Type
	{
		FirstAidKit,
		HealthPotion,
		PelletGun,
		Flamethrower,
		Key,
		Dynamite
	};
}

namespace Enemies
{
	enum Name
	{
		Zombie,
		TommyTheDoll,
		GiantAnt,
		MutantPlant,
	};
}

namespace Weapons
{
	enum Type
	{
		PelletGun,
		Flamethrower
	};
}

namespace GameObjects
{
	enum Type
	{
		Player,
		Obstacle,
		Closet,
		Door,
		Bullet,
		FirstAidKit,
		HealthPotion,
		PistolAmmo,
		FlameThrowerAmmo,
		Key,
		Dynamite,
		GiantAnt,
		MutantPlant,
		TommyTheDoll,
		Zombie,
		Man,
		Baby,
		Puppy,
		Tourists,
		Teacher,
		Cheerleader
	};
};

const std::unordered_map<std::string, GameObjects::Type> stringToTypeMap =
{
	{ "Player", GameObjects::Player },
	{ "Obstacle", GameObjects::Obstacle },
	{ "Closet", GameObjects::Closet },
	{ "Door", GameObjects::Door },
	{ "FirstAidKit", GameObjects::FirstAidKit },
	{ "HealthPotion", GameObjects::HealthPotion },
	{ "PistolAmmo", GameObjects::PistolAmmo },
	{ "FlameThrowerAmmo", GameObjects::FlameThrowerAmmo },
	{ "Bullet", GameObjects::Bullet },
	{ "GiantAnt", GameObjects::GiantAnt },
	{ "MutantPlant", GameObjects::MutantPlant },
	{ "TommyTheDoll", GameObjects::TommyTheDoll },
	{ "Zombie", GameObjects::Zombie },
	{ "Key", GameObjects::Key },
	{ "Dynamite", GameObjects::Dynamite},
	{ "Man", GameObjects::Man},
	{ "Baby", GameObjects::Baby},
	{ "Puppy", GameObjects::Puppy},
	{ "Tourists", GameObjects::Tourists},
	{ "Teacher", GameObjects::Teacher},
	{ "Cheerleader", GameObjects::Cheerleader}
};

struct SpriteInfo {
	sf::IntRect rect;
	sf::Vector2f pivot;
	bool rotated;
};

const std::unordered_map<GameObjects::Type, std::string> OBJECT_TEXTURE_MAP = {
		{GameObjects::Type::Player, "idle"},
		{GameObjects::Type::Bullet, "Bullet"},
		{GameObjects::Type::Dynamite, "Dynamite"},
		{GameObjects::Type::PistolAmmo, "PelletGun"},
		{GameObjects::Type::FlameThrowerAmmo, "FlameThrower"},
		{GameObjects::Type::Key, "Key"},
		{GameObjects::Type::FirstAidKit, "FirstAidKit"},
		{GameObjects::Type::HealthPotion, "HealthPotion"},
		{GameObjects::Type::GiantAnt, "GiantAnt"},
		{GameObjects::Type::MutantPlant, "Plant"},
		{GameObjects::Type::TommyTheDoll, "TommyTheDoll"},
		{GameObjects::Type::Zombie, "Zombie"},
		{GameObjects::Type::Baby, "Baby"},
		{GameObjects::Type::Cheerleader, "Cheerleader"},
		{GameObjects::Type::Man, "Man"},
		{GameObjects::Type::Puppy, "Puppy"},
		{GameObjects::Type::Teacher, "Teacher"},
		{GameObjects::Type::Tourists, "Tourists"}
};