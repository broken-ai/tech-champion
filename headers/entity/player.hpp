#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

class Player : public Entity {
private:
    bool shot;

public:
    sf::View view;
    uint8_t playerID;
    int cameraX;
    int cameraY;

    Player(const int &playerID, int startX, int startY);
    ~Player();
    void update(Map* inMap);
};

#endif  // _PLAYER_HPP_
