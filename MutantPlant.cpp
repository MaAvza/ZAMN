#include "Objects/MobileObjects/MutantPlant.h"
#include "Strategy/StayInPLaceBehavior.h"


MutantPlant::MutantPlant(sf::Texture* texture,
    const sf::Vector2f& position, 
    float shootInterval, 
    float projectileSpeed, 
    float projectileDamage,
    ProjectileManager& projectileManager)
    : Enemy(texture, position), 
    m_shootInterval(shootInterval), 
    m_shootTimer(0.f), 
    m_projectileSpeed(projectileSpeed), 
    m_projectileDamage(projectileDamage),
    m_projectileManager(projectileManager)
{
    setBehavior(std::make_unique<StayInPlaceBehavior>(this));
}

MutantPlant::MutantPlant(const MutantPlant& other, ProjectileManager& newProjectileManager)
    : Enemy(other),  // Call the default copy constructor of Enemy
    m_projectileManager(newProjectileManager),
    m_shootInterval(other.m_shootInterval),
    m_shootTimer(other.m_shootTimer),
    m_projectileSpeed(other.m_projectileSpeed),
    m_projectileDamage(other.m_projectileDamage)
{
    // set correct behavior
    setBehavior(std::make_unique<StayInPlaceBehavior>(this));
}

void MutantPlant::update(float deltaTime, const sf::Vector2f& mapSize)
{
    m_shootTimer += deltaTime;
    if (m_shootTimer >= m_shootInterval)
    {
        shootRandomly();
        m_shootTimer = 0.f;
    }
}

std::unique_ptr<Enemy> MutantPlant::clone(const sf::Vector2f& position) const
{
    return std::make_unique<MutantPlant>(*this, m_projectileManager);
}

Enemies::Name MutantPlant::getType() const
{
    return Enemies::Name::MutantPlant;
}

void MutantPlant::shootRandomly()
{
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;
    sf::Vector2f direction(std::cos(angle), std::sin(angle));
    std::unique_ptr<ExplosiveProjectile> projectile = std::make_unique<ExplosiveProjectile>(
        ResourceManager::getInstance()->getTexture("Blob"),
        m_position,
        direction,
        m_projectileSpeed,
        m_projectileDamage,
        100.0f,
        5.0f,
        sf::Color::Magenta
    );
    m_projectileManager.addProjectile(std::move(projectile));
}
