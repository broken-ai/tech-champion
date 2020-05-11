#include "../../headers/object/basic_bullet.hpp"


BasicBullet::BasicBullet(const float &xPos, const float &yPos, const DIRECTION direction, const uint8_t &creatorID) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->xSpeed = BasicBullet::baseSpeed;
    this->ySpeed = BasicBullet::baseSpeed;
    this->creatorID = creatorID;
    this->lifeTimeCounter = 0;
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();

    // Set speed to set direction
    if (direction == DIRECTION::UP) {
        //cout << "UP" << endl;
        this->xSpeed *= 0;
        this->ySpeed *= -1;
    }
    else if (direction == DIRECTION::RIGHT_UP) {
        //cout << "RIGHT_UP" << endl;
        this->xSpeed *= 1;
        this->ySpeed *= -1;
    }
    else if (direction == DIRECTION::RIGHT) {
        //cout << "RIGHT" << endl;
        this->xSpeed *= 1;
        this->ySpeed *= 0;
    }
    else if (direction == DIRECTION::RIGHT_DOWN) {
        //cout << "RIGHT_DOWN" << endl;
        this->xSpeed *= 1;
        this->ySpeed *= 1;
    }
    else if (direction == DIRECTION::DOWN) {
        //cout << "DOWN" << endl;
        this->xSpeed *= 0;
        this->ySpeed *= 1;
    }
    else if (direction == DIRECTION::LEFT_DOWN) {
        //cout << "LEFT_DOWN" << endl;
        this->xSpeed *= -1;
        this->ySpeed *= 1;
    }
    else if (direction == DIRECTION::LEFT) {
        //cout << "LEFT" << endl;
        this->xSpeed *= -1;
        this->ySpeed *= 0;
    }
    else if (direction == DIRECTION::LEFT_UP) {
        //cout << "LEFT_UP" << endl;
        this->xSpeed *= -1;
        this->ySpeed *= -1;
    }

    // Load in the sprite of the bullet
    const std::string bulletFileName = BASE_FOLDER + BULLET_FOLDER + "basic_bullet.png";
    if (!this->texture->loadFromFile(bulletFileName)) {
        openMessageBox("ERROR: Bullet texture file (" + bulletFileName + ") cannot be opened.");
        exit(EXIT_FAILURE);
    }
    this->sprite->setTexture(*this->texture);
}

void BasicBullet::update(Map* inMap) {
    this->xPos += this->xSpeed;
    this->yPos += this->ySpeed;
    this->lifeTimeCounter++;
}

void BasicBullet::draw(sf::RenderWindow* inWindow) {
    this->sprite->setPosition(this->xPos, this->yPos);
    inWindow->draw(*this->sprite);
}

BasicBullet::~BasicBullet() {
    delete &this->xPos;
    delete &this->yPos;
    delete &this->xSpeed;
    delete &this->xSpeed;
    delete &this->creatorID;
    delete &this->sprite;
}
