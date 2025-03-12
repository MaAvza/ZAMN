#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "tinyxml2.h"
#include "Globals.h"

class ResourceManager
{
public:
    static ResourceManager* getInstance();
    void loadResources();
    void loadTexture(const std::string& path);
    void loadFont(const std::string& path);
    void loadSpriteSheet(const std::string& texturePath, const std::string& xmlPath);

    sf::Texture* getTexture(const std::string& name) const;
    sf::Font* getFont(const std::string& path);
    sf::Sprite getSprite(const std::string& sheetName, const std::string& spriteName) const;

private:
    ResourceManager() : m_font(nullptr) {};
    ~ResourceManager();

    static ResourceManager* m_instance;

    sf::Font* m_font;
    std::unordered_map<std::string, sf::Texture*> m_textures;
    std::unordered_map<std::string, std::unordered_map<std::string, SpriteInfo>> m_spriteSheets;

    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::string extractName(const std::string& path) const;
    bool parseSpriteSheetXML(const std::string& xmlPath, const std::string& sheetName);
};

//class ResourceManager
//{
//public:
//	static ResourceManager* getInstance();
//	void loadResources();
//	void loadTexture(const std::string& path);
//	void loadFont(const std::string& path);
//
//	sf::Texture* getTexture(const std::string& name) const;
//	sf::Font* getFont(const std::string& path);
//
//private:
//	ResourceManager() : m_font(nullptr) {};
//	~ResourceManager();
//
//	static ResourceManager* m_instance;
//
//	sf::Font* m_font;
//	std::unordered_map<std::string, sf::Texture*> m_textures;
//
//	/* deleted operators */
//	ResourceManager(const ResourceManager&) = delete;		     // should not be cloneable
//	void operator=(const ResourceManager&&) = delete;		     // should not be movable
//	ResourceManager& operator=(const ResourceManager&) = delete; // should not be assignable
//
//	std::string extractName(const std::string& path) const; //get the name of the file without extensions
//
//};