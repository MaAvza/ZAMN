#pragma once
#include <SFML/System/Vector2.hpp>

class IPlayerObserver {
public:
    virtual ~IPlayerObserver() = default;
    virtual void onPlayerPositionUpdate(const sf::Vector2f& playerPosition) = 0;
};
