#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

class ResourceManager {
public:
    bool isLoaded;
    std::vector<sf::Texture*> animTextures; // Textures loaded from PNG files inside animation set files
    std::vector<AnimSet*> animSets;
    std::vector<Bullet*> bullets;

    ResourceManager();
    const bool load();
    const Animation getAnim(const std::string &animSetName, const int &animIndex);
    const void update();
};

// Declare it as a global variable
ResourceManager g_rm;

#endif // _RESOURCE_MANAGER_HPP_
