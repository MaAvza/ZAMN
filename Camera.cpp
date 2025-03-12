#include "Utility/Camera.h"

Camera::Camera()
    : m_view(sf::FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y)),
    m_mapSize(WINDOW_SIZE.x, WINDOW_SIZE.y),
    m_zoom(2.0f)  
{
    m_view.setCenter(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
    m_view.setSize(WINDOW_SIZE.x / m_zoom, WINDOW_SIZE.y / m_zoom);
}

Camera::Camera(sf::Vector2f viewSize, sf::Vector2f mapSize)
    : m_view(sf::FloatRect(0, 0, viewSize.x, viewSize.y)), m_mapSize(mapSize), m_zoom(2.0f)
{
    m_view.setCenter(viewSize.x / 2, viewSize.y / 2);
    m_view.setSize(viewSize.x / m_zoom, viewSize.y / m_zoom);
}


void Camera::setMapSize(sf::Vector2f mapSize)
{
	m_mapSize = mapSize;
	applyBounds();
}

void Camera::setViewSize(sf::Vector2f viewSize)
{
	m_view.setSize(viewSize);
	applyBounds();
}

void Camera::update(const sf::Vector2f& targetPosition)
{
    m_view.setCenter(targetPosition);
    applyBounds();
}

void Camera::zoom(float factor)
{
    m_zoom = std::clamp(m_zoom * (1.0f + factor * ZOOM_SPEED), MIN_ZOOM, MAX_ZOOM);
    m_view.setSize(m_view.getSize().x / m_zoom, m_view.getSize().y / m_zoom);
    applyBounds();
}

const sf::View& Camera::getView() const
{
    return m_view;
}

void Camera::applyBounds()
{
    sf::Vector2f viewSize = m_view.getSize();
    sf::Vector2f viewCenter = m_view.getCenter();

    float left = std::max(viewSize.x / 2.0f, 0.0f);
    float top = std::max(viewSize.y / 2.0f, 0.0f);
    float right = std::max(left, std::min(m_mapSize.x - viewSize.x / 2.0f, m_mapSize.x));
    float bottom = std::max(top, std::min(m_mapSize.y - viewSize.y / 2.0f, m_mapSize.y));

    float newX = clamp(viewCenter.x, left, right);
    float newY = clamp(viewCenter.y, top, bottom);

    m_view.setCenter(newX, newY);
}

float Camera::clamp(float value, float min, float max) const
{
    if (min > max) {
        std::cerr << "Warning: Invalid clamp bounds (min > max). Min: " << min << ", Max: " << max << std::endl;
        return value;  // Return the original value if bounds are invalid
    }
    return std::min(std::max(value, min), max);
}