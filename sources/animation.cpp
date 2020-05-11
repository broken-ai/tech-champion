#include "../headers/animation.hpp"


Animation::Animation() {
    this->frameCount = 0;
    this->speed = 1;
    this->curFrame = 0;
    this->width = 0;
    this->height = 0;
    this->flipped = 0;
    this->counter.restart();
}

void Animation::reset() {
    this->curFrame = 0;
    this->counter.restart();
}

void Animation::play(const int &xPos, const int &yPos, const bool &draw, sf::RenderWindow* inWindow=nullptr) {
    for (int i = 0; i < this->frameCount;i++) this->frames[i].setPosition(xPos, yPos);

    if (this->speed > 0) {
        if (this->counter.getElapsedTime().asMilliseconds() >= (1000 / this->speed)) {
            /*if (++this->curFrame >= this->frameCount) {
                this->curFrame = 0;
            }*/
            if (this->curFrame < this->frameCount - 1) curFrame++;
            else curFrame = 0;

            this->counter.restart();
        }
    }

    if (draw && inWindow !=nullptr) {
        inWindow->draw(this->frames[curFrame]);
    }
}

void Animation::setFlip(const int16_t &direction=1) {
    if (direction == -1 && !this->flipped) {
        for (int i = 0; i < this->frameCount; i++) {
            this->frames[i].setScale(-1, 1);
        }
        this->flipped = true;
    } else if (direction == 1 && this->flipped) {
         for (int i = 0; i < this->frameCount; i++) {
            this->frames[i].setScale(1, 1);
        }
        this->flipped = false;
    }
}

void Animation::setSpeed(const unsigned int &speed) {
    if (speed > 0 && speed < 999) this->speed = speed;
}

void Animation::setFrame(const unsigned int &frame) {
    this->curFrame = frame;
}

Animation::~Animation() {}
