#ifndef _BOT_HPP_
#define _BOT_HPP_

enum class BOT_STATE {
    PATROL,
    CHASE
};

enum class BOT_DIFFICULTY {
    NOOB,
    ROOKIE,
    INTERMEDIATE,
    EXPERIENCED,
    GOD
};

class Bot : public Entity {
    /**
    Class for AI enemies
    */
public:
    const static unsigned int patrolingCounterChangeAt = 50;

    BOT_DIFFICULTY difficulty;
    BOT_STATE state;
    unsigned int patrolingCounter;
    unsigned int sightDistance;
    DIRECTION currentEnemyDirection;
    DIRECTION lastEnemyDirection;
    DIRECTION moveDirection;
    DIRECTION aimDirection;
    bool shouldShoot;

    Bot(const uint16_t xPos, const uint16_t yPos, const BOT_DIFFICULTY difficulty);
    ~Bot();
    void update(Map* inMap);
    const bool updateState(Map* map, Entity* opponent);

private:
    const DIRECTION whereIsOpponent(Entity* opponent);
    const bool updateBasicState(Map *map, Entity *opp);
};

#endif // _BOT_HPP_
