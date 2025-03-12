#pragma once
#include "Objects/MobileObjects/Zombie.h"
#include "Objects/MobileObjects/Player.h"
#include "Objects/StaticObjects/Obstacle.h"
#include "Objects/MobileObjects/FlameThrowerProjectile.h"
#include "Objects/MobileObjects/PelletGunProjectile.h"
#include "Objects/MobileObjects/Survivor.h"
#include "Objects/StaticObjects/FirstAidKit.h"
#include "Objects/StaticObjects/HealthPotion.h"
#include "Objects/StaticObjects/Key.h"
#include "Objects/StaticObjects/Dynamite.h"
#include "Objects/StaticObjects/PelletGun.h"
#include "Objects/StaticObjects/FlameThrower.h"
#include "Objects/StaticObjects/PistolAmmo.h"
#include "Objects/StaticObjects/FlameThrowerAmmo.h"
#include "Objects/MobileObjects/GiantAnt.h"
#include "Objects/MobileObjects/MutantPlant.h"
#include "Objects/MobileObjects/TommyTheDoll.h"
#include "Objects/StaticObjects/Door.h"
#include "Objects/StaticObjects/Closet.h"

#include <map>
#include <typeindex>
#include <stdexcept>
#include <iostream>
#include <typeinfo>

struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(GameObject& object1, GameObject& object2);
