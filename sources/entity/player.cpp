#include "../../headers/entity/player.hpp"


Player::Player(const int &playerID = 0, int startX = 0, int startY = 0) {
    this->xPos = startX;
    this->yPos = startY;
    this->view.reset(sf::FloatRect(0, 0, g_config.WINDOW_WIDTH, g_config.WINDOW_HEIGHT));
    this->playerID = playerID;
    this->cameraX = 0;
    this->cameraY = 0;
    this->invincibility.restart();
    this->shot = false;
    this->direction = 1;
    this->aimDirection = DIRECTION::RIGHT;
    this->animSetName = "player";
}

void Player::update(Map* inMap) {

    // Gravity and jumping
    const int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        this->yPos += distFromGround;
        this->ySpeed = 0;
        this->jumpCount = 0;
        if (sf::Keyboard::isKeyPressed(g_config.JUMP) && this->jumpCount < this->jumpLimit) {
            this->ySpeed = -1 * this->jumpPower;
            this->jumpCount++;
        }
    } else if (this->ySpeed < 20) {
        this->ySpeed += GRAVITY_CONST;
        if (this->ySpeed < 0 && this->jumpCount > 0 && !sf::Keyboard::isKeyPressed(g_config.JUMP)) ySpeed /= 1.5;
    }

    const int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (distFromCeiling > -10 && distFromCeiling >= this->ySpeed) {
        this->ySpeed = 1;
        this->yPos += distFromCeiling;
    }

    // Handle keystrokes - X axis
    if (sf::Keyboard::isKeyPressed(g_config.LEFT)) {
        if (!sf::Keyboard::isKeyPressed((g_config.AIM_LOCK))) {
            if (xSpeed >= -6) xSpeed -= .3;
            else xSpeed = -6;

            int temp = maskedTopVLine(inMap, 4, this->xPos - 14, this->yPos + 27, 8);
            if (temp < 8) {
                this->yPos += -4 + temp;
                if (temp < 2) {
                    if (xSpeed < -4) xSpeed = -4;
                }
            }
        } else this->xSpeed = 0;

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(g_config.UP)) {
            this->aimDirection = DIRECTION::LEFT_UP;
        }
        else if (sf::Keyboard::isKeyPressed(g_config.DOWN)) {
            this->aimDirection = DIRECTION::LEFT_DOWN;
        }
        else {
            this->aimDirection = DIRECTION::LEFT;
        }
    }
    else if (sf::Keyboard::isKeyPressed(g_config.RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((g_config.AIM_LOCK))) {
            if (xSpeed <= 6) xSpeed += .3;
            else xSpeed = 6;

            int temp = maskedTopVLine(inMap, 4, this->xPos + 13, this->yPos + 27, 8);
            if (temp < 8) {
                this->yPos += -4 + temp;
                if (temp < 2) {
                    if (xSpeed > 4) xSpeed = 4;
                }
            }
        } else this->xSpeed = 0;

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(g_config.UP)) {
            this->aimDirection = DIRECTION::RIGHT_UP;
        }
        else if (sf::Keyboard::isKeyPressed(g_config.DOWN)) {
            this->aimDirection = DIRECTION::RIGHT_DOWN;
        }
        else {
            this->aimDirection = DIRECTION::RIGHT;
        }
    }
    else {
        this->xSpeed = 0;
    }

    if (sf::Keyboard::isKeyPressed(g_config.UP) && !(sf::Keyboard::isKeyPressed(g_config.LEFT) || sf::Keyboard::isKeyPressed(g_config.RIGHT))) {
        this->aimDirection = DIRECTION::UP;
    }
    if (sf::Keyboard::isKeyPressed(g_config.DOWN) && !(sf::Keyboard::isKeyPressed(g_config.LEFT) || sf::Keyboard::isKeyPressed(g_config.RIGHT))) {
        this->aimDirection = DIRECTION::DOWN;
    }

    const int lWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos - 10, this->yPos - 30, -8, this->height - 9);
    const int rWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos + 9, this->yPos - 30, 8, this->height - 9);

    if (this->xSpeed <= 0 && lWallIntrusion > -8) {
        this->xSpeed = 0;
        this->xPos += 7 + lWallIntrusion;
    }
    if (this->xSpeed >= 0 && rWallIntrusion < 8) {
        this->xSpeed = 0;
        this->xPos += -7 + rWallIntrusion;
    }

    this->xPos += this->xSpeed;
    this->yPos += this->ySpeed;
    this->cameraX = this->xPos - g_config.WINDOW_WIDTH / 2;
    this->cameraY = this->yPos - g_config.WINDOW_HEIGHT / 2;
    this->view.setCenter(this->cameraX + g_config.WINDOW_WIDTH / 2, this->cameraY + g_config.WINDOW_HEIGHT / 2);

    // Shooting in the player's direction
    if (!this->shot && sf::Keyboard::isKeyPressed(g_config.SHOOT)) {
        g_rm.bullets.push_back(new BasicBullet(this->xPos, this->yPos, this->aimDirection, this->playerID));
    }

    this->shot = sf::Keyboard::isKeyPressed(g_config.SHOOT);
}

Player::~Player() {}
