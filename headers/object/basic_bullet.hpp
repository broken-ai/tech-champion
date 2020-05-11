#ifndef _BASIC_BULLET_HPP_
#define _BASIC_BULLET_HPP_

class BasicBullet : public Bullet {
public:
    const static int maxLifeTime = 100;
    const static int baseSpeed = 10;

    BasicBullet(const float &xPos, const float &yPos, const DIRECTION direction, const uint8_t &creatorID);
    ~BasicBullet();
    void update(Map* inMap);
    void draw(sf::RenderWindow* inWindow);
};

#endif  // _BASIC_BULLET_HPP_
