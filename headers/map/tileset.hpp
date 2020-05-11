#ifndef _TILESET_HPP_
#define _TILESET_HPP_

class Tileset {
public:
    sf::Texture texture;
    std::vector<std::vector<bool>> mask; // Contains the collision data of the tileset
    std::vector<sf::Sprite> tileSprites; // The drawable sprite for each tile

    Tileset();
    ~Tileset();
    void initialize(const std::string &filepath);
};

#endif // _TILESET_HPP_
