#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

class Entity {
    /**
    Represents an abstract class for movable entities
    */
public:
    DIRECTION aimDirection;
    uint8_t jumpCount = 0;
    uint8_t jumpLimit = 1;
    uint8_t jumpPower = 12;

    float xPos = 64;
    float yPos = 64;
    float xSpeed = 0;
    float ySpeed = 0;
    const uint8_t width = 32;
    const uint8_t height = 64;
    uint8_t health = STARTING_HEALTH;
    sf::Clock invincibility;
    int8_t direction;  // -1 for left, 1 for right
    std::string animSetName;
    Animation anim;

    virtual void update(Map* inMap) = 0;
    const bool loadSkin(const std::string &filename);
    const void draw(sf::RenderWindow* window);
};

#endif // _ENTITY_HPP_
