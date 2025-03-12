#include "Utility/ResourceManager.h"
#include <iostream>

ResourceManager* ResourceManager::m_instance = nullptr;

ResourceManager* ResourceManager::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new ResourceManager();
    }
    return m_instance;
}

ResourceManager::~ResourceManager()
{
    for (auto& texture : m_textures)
    {
        delete texture.second;
        texture.second = nullptr;
    }
    delete m_font;
    m_font = nullptr;
}

void ResourceManager::loadResources()
{
    loadFont("Scaryfeet.ttf");
    loadTexture("ScreenBG.jpg");
    loadTexture("idle.png");
    loadTexture("Bullet.png");
    loadTexture("Dynamite.png");
    loadTexture("PelletGun.png");
    loadTexture("FlameThrower.png");
    loadTexture("Key.png");
	loadTexture("FirstAidKit.png");
    loadTexture("HealthPotion.png");
    loadTexture("GiantAnt.png");
    loadTexture("MutantPlant.png");
    loadTexture("TommyTheDoll.png");
    loadTexture("zombie.png");
    loadSpriteSheet("Baby.png", "Baby.xml");
    loadSpriteSheet("Cheerleader.png", "Cheerleader.xml");
    loadSpriteSheet("Man.png", "Man.xml");
    loadSpriteSheet("Puppy.png", "Puppy.xml");
    loadSpriteSheet("Teacher.png", "Teacher.xml");
    loadSpriteSheet("Tourists.png", "Tourists.xml");
}

void ResourceManager::loadTexture(const std::string& path)
{
    sf::Texture* texture = new sf::Texture();

    if (!texture->loadFromFile(path))
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        delete texture;
    }
    else
    {
        std::string name = extractName(path);
        m_textures[name] = texture;
    }
}

void ResourceManager::loadFont(const std::string& path)
{
    sf::Font* font = new sf::Font();
    if (!font->loadFromFile(path))
    {
        std::cerr << "Failed to load font: " << path << std::endl;
        delete font;
        m_font = nullptr;
    }
    else
        m_font = font;
}

void ResourceManager::loadSpriteSheet(const std::string& texturePath, const std::string& xmlPath)
{
    loadTexture(texturePath);
    std::string sheetName = extractName(texturePath);
    if (!parseSpriteSheetXML(xmlPath, sheetName))
    {
        std::cerr << "Failed to load sprite sheet: " << sheetName << std::endl;
    }
}

sf::Texture* ResourceManager::getTexture(const std::string& name) const
{
    auto it = m_textures.find(name);
    if (it != m_textures.end() && it->second != nullptr)
    {
        return it->second;
    }
    std::cerr << "Texture not found: " << name << std::endl;
    return nullptr;
}

sf::Font* ResourceManager::getFont(const std::string& path)
{
    if (m_font == nullptr)
    {
        std::cerr << "Font not loaded" << std::endl;
    }
    return m_font;
}

sf::Sprite ResourceManager::getSprite(const std::string& sheetName, const std::string& spriteName) const
{
    auto sheetIt = m_spriteSheets.find(sheetName);
    if (sheetIt == m_spriteSheets.end())
    {
        std::cerr << "Sprite sheet not found: " << sheetName << std::endl;
        return sf::Sprite();
    }

    auto spriteIt = sheetIt->second.find(spriteName);
    if (spriteIt == sheetIt->second.end())
    {
        std::cerr << "Sprite not found: " << spriteName << " in sheet: " << sheetName << std::endl;
        return sf::Sprite();
    }

    const SpriteInfo& info = spriteIt->second;

    sf::Sprite sprite(*getTexture(sheetName), info.rect);
    sprite.setOrigin(info.pivot);

    if (info.rotated)
    {
        sprite.setRotation(90);
        sprite.setOrigin(info.pivot.y, info.rect.width - info.pivot.x);
    }

    return sprite;
}

std::string ResourceManager::extractName(const std::string& path) const
{
    size_t lastDot = path.find_last_of('.');

    if (lastDot == std::string::npos) {
        return path;  // No extension present
    }
    
    return path.substr(0, lastDot);
}

bool ResourceManager::parseSpriteSheetXML(const std::string& xmlPath, const std::string& sheetName)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xmlPath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Failed to load XML file: " << xmlPath << std::endl;
        return false;
    }

    tinyxml2::XMLElement* atlas = doc.FirstChildElement("TextureAtlas");
    if (!atlas)
    {
        std::cerr << "Invalid XML format: Missing TextureAtlas element" << std::endl;
        return false;
    }

    for (tinyxml2::XMLElement* sprite = atlas->FirstChildElement("sprite"); sprite; sprite = sprite->NextSiblingElement("sprite"))
    {
        std::string name = sprite->Attribute("n");
        int x = sprite->IntAttribute("x");
        int y = sprite->IntAttribute("y");
        int w = sprite->IntAttribute("w");
        int h = sprite->IntAttribute("h");
        float pX = sprite->FloatAttribute("pX", 0.5f);
        float pY = sprite->FloatAttribute("pY", 0.5f);
        bool rotated = (sprite->Attribute("r") != nullptr);

        SpriteInfo info;
        info.rect = sf::IntRect(x, y, w, h);
        info.pivot = sf::Vector2f(pX * w, pY * h);
        info.rotated = rotated;

        m_spriteSheets[sheetName][name] = info;
    }

    return true;
}
