#include "../headers/stats_table.hpp"


StatsTable::StatsTable(std::vector<Bot*> entities, Player *player,
                        const int &width=g_config.WINDOW_WIDTH - 64,
                        const int &height=g_config.WINDOW_HEIGHT - 64) {
    this->entities = entities;
    this->player = player;
    this->width = width;
    this->height = height;

    this->body.setSize(sf::Vector2f(this->width, this->height));
    this->body.setFillColor(sf::Color(37, 37, 37, 100));
    this->body.setPosition(g_config.WINDOW_WIDTH / 2, g_config.WINDOW_HEIGHT / 2);
}

const void StatsTable::show(sf::RenderWindow *window) {
    sf::Vector2f viewCenter = window->getView().getCenter();
    viewCenter.x -= this->width / 2;
    viewCenter.y -= this->height / 2;
    this->body.setPosition(viewCenter);
    window->draw(this->body);
}
