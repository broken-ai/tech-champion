#include "../../headers/entity/entity.hpp"


const void Entity::draw(sf::RenderWindow* window) {
    this->anim.play(this->xPos, this->yPos, true, window);
    this->anim.setFlip(this->direction);
}

const bool Entity::loadSkin(const std::string &filepath) {
    this->anim = g_rm.getAnim(this->animSetName, 0);
    this->anim.setSpeed(30);
    return true;
}

#include "player.cpp"
#include "bot.cpp"
