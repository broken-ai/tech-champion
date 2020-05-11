#ifndef _STATS_TABLE_HPP_
#define _STATS_TABLE_HPP_

class StatsTable {
public:
    std::vector<Bot*> entities;
    Player *player;
    sf::RectangleShape body;
    int width;
    int height;

    StatsTable(std::vector<Bot*> entities, Player *player, const int &width, const int &height);
    const void show(sf::RenderWindow *window);
};

#endif // _STATS_TABLE_HPP_
