#pragma once
#include "StaticObject.h"

class Player;

class CollectibleItem : public StaticObject
{
public:
    CollectibleItem();
    CollectibleItem(sf::Texture* texture, const sf::Vector2f& position);
    virtual ~CollectibleItem() = default;

    virtual void onCollect(class Player& player) = 0;
    virtual bool isConsumable() const = 0;
    virtual std::string getName() const = 0;
};