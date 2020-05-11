#ifndef _BULLET_HPP_
#define _BULLET_HPP_

class Bullet {
    /**
    Abstract bullet.
    */
public:
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    uint8_t creatorID;
    int lifeTimeCounter;
    sf::Texture* texture;
    sf::Sprite* sprite;

    virtual void update(Map* inMap) = 0;
    virtual void draw(sf::RenderWindow* inWindow) = 0;
};

#endif  // _BULLET_HPP_
