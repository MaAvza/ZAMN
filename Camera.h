#pragma once
#include "Globals.h"
#include <algorithm>
#include <iostream>

class Camera
{
public:
    Camera();
    Camera(sf::Vector2f viewSize, sf::Vector2f mapSize);

    void setMapSize(sf::Vector2f mapSize);
    void setViewSize(sf::Vector2f viewSize);
    void update(const sf::Vector2f& targetPosition);
    void zoom(float factor);
    const sf::View& getView() const;

private:
    sf::View m_view;
    sf::Vector2f m_mapSize;
    float m_zoom;
    
    void applyBounds();
    float clamp(float value, float min, float max) const;
};