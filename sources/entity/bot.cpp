#include "../../headers/entity/bot.hpp"


Bot::Bot(const uint16_t xPos=64, const uint16_t yPos=64, const BOT_DIFFICULTY difficulty=BOT_DIFFICULTY::ROOKIE) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->difficulty = difficulty;
    this->state = BOT_STATE::PATROL;
    this->patrolingCounter = 0;
    this->direction = 1;
    this->invincibility.restart();
    this->sightDistance = g_config.WINDOW_WIDTH / 2 + 96;
    this->currentEnemyDirection = DIRECTION::UNKNOWN;
    this->lastEnemyDirection = DIRECTION::UNKNOWN;
    this->shouldShoot = false;
    this->animSetName = "bot";
}

void Bot::update(Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        this->yPos += distFromGround;
        this->ySpeed = 0;
        this->jumpCount = 0;
        if ((this->moveDirection == DIRECTION::UP || this->moveDirection == DIRECTION::LEFT_UP || this->moveDirection == DIRECTION::RIGHT_UP)
                && this->jumpCount < this->jumpLimit) {
            this->ySpeed = -this->jumpPower;
            jumpCount++;
        }
    } else if (this->ySpeed < 20) this->ySpeed += GRAVITY_CONST;

    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (distFromCeiling > -10 && distFromCeiling >= this->ySpeed) {
        this->ySpeed = 1;
        this->yPos += distFromCeiling;
    }

    // Handle keystrokes - X axis
    if (this->moveDirection == DIRECTION::LEFT || this->moveDirection == DIRECTION::LEFT_UP || this->moveDirection == DIRECTION::LEFT_DOWN) {
        if (xSpeed >= -6) xSpeed -= .3;
        else xSpeed = -6;
        this->direction = -1;

        int temp = maskedTopVLine(inMap, 4, this->xPos - 14, this->yPos + 27, 8);
        if (temp < 8) {
            this->yPos += -4 + temp;
            if (temp < 2) {
                if (xSpeed < -4) xSpeed = -4;
            }
        }

    }
    else if (this->moveDirection == DIRECTION::RIGHT || this->moveDirection == DIRECTION::RIGHT_UP || this->moveDirection == DIRECTION::RIGHT_DOWN) {
        if (xSpeed <= 6) xSpeed += .3;
        else xSpeed = 6;
        this->direction = 1;

        int temp = maskedTopVLine(inMap, 4, this->xPos + 13, this->yPos + 27, 8);
        if (temp < 8) {
            this->yPos += -4 + temp;
            if (temp < 2) {
                if (xSpeed > 4) xSpeed = 4;
            }
        }
    }
    else {
        this->xSpeed = 0;
    }

    int lWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos - 10, this->yPos - 30, -8, this->height - 7);
    int rWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos + 9, this->yPos - 30, 8, this->height - 7);

    if (this->xSpeed <= 0 && lWallIntrusion > -8) {
        this->xSpeed = 0;
        this->xPos += 7 + lWallIntrusion;
    }
    if (this->xSpeed >= 0 && rWallIntrusion < 8) {
        this->xSpeed = 0;
        this->xPos += -7 + rWallIntrusion;
    }

    if (this->shouldShoot) {
        // g_rm.bullets.push_back(new BasicBullet(this->xPos, this->yPos, this->aimDirection, -1));
    }

    this->xPos += this->xSpeed;
    this->yPos += this->ySpeed;
}

const DIRECTION Bot::whereIsOpponent(Entity *opp) {
    int dx = opp->xPos - this->xPos;
    int dy = opp->yPos - this->yPos;

    // Determine where is the enemy
    if (std::abs(dx) < this->sightDistance && dx != 0 && dy != 0) {
        float deg = 180 / M_PI * std::atan2(dy, dx);
        if (deg < 0) deg = 360 + deg;

        if (deg >= 22.5 && deg <= 67.5) {
            return DIRECTION::RIGHT_DOWN;
        }
        else if (deg >= 67.5 && deg <= 112.5) {
            return DIRECTION::DOWN;
        }
        else if (deg >= 112.5 && deg <= 157.5) {
            return DIRECTION::LEFT_DOWN;
        }
        else if (deg >= 157.5 && deg <= 202.5) {
            return DIRECTION::LEFT;
        }
        else if (deg >= 202.5 && deg <= 247.5) {
            return DIRECTION::LEFT_UP;
        }
        else if (deg >= 247.5 && deg <= 292.5) {
            return DIRECTION::UP;
        }
        else if (deg >= 292.5 && deg <= 337.5) {
            return DIRECTION::RIGHT_UP;
        }
        else {  // if (deg >= 337.5 && deg <= 22.5)
            return DIRECTION::RIGHT;
        }
    }
    return DIRECTION::UNKNOWN;
}

const bool Bot::updateState(Map *map, Entity *opp) {
    float dx = opp->xPos - this->xPos;

    // Chase the opponent if it can be seen
    if (std::abs(dx) < this->sightDistance) {
        this->state = BOT_STATE::CHASE;
    }
    else {
        this->state = BOT_STATE::PATROL;
    }

    if (this->state == BOT_STATE::PATROL) {  // Move back and forth between two points
        this->patrolingCounter++;

        if (this->patrolingCounter <= Bot::patrolingCounterChangeAt) {
            this->moveDirection = DIRECTION::RIGHT;
        }
        else if (this->patrolingCounter > Bot::patrolingCounterChangeAt && this->patrolingCounter < 3 * Bot::patrolingCounterChangeAt) {
            this->moveDirection = DIRECTION::LEFT;
        }
        else if (this->patrolingCounter >= 3 * Bot::patrolingCounterChangeAt) {
            this->patrolingCounter = 0;
        }
    }
    else {
        this->currentEnemyDirection = this->whereIsOpponent(opp);  // Determine where is the opponent

        if (this->currentEnemyDirection == DIRECTION::UNKNOWN) {  // In this case go to the last seen position of the player
            this->currentEnemyDirection = this->lastEnemyDirection;

            if (rand() % 2 == 0) {
                this->currentEnemyDirection = DIRECTION::LEFT;
            }
            else {
                this->currentEnemyDirection = DIRECTION::RIGHT;
            }
        }
        else {
            this->lastEnemyDirection = this->currentEnemyDirection;
        }

        // Set aim and basic moving direction
        this->aimDirection = this->currentEnemyDirection;
        this->moveDirection = this->currentEnemyDirection;
    }

    // Determine where it's possible to move
    if ((this->moveDirection == DIRECTION::RIGHT || this->moveDirection == DIRECTION::RIGHT_UP)
            && !maskedHLine(map, 4, this->xPos, this->yPos, 32)) {  // No obstacle on the right side
        this->moveDirection = DIRECTION::RIGHT;
    }
    else if ((this->moveDirection == DIRECTION::LEFT || this->moveDirection == DIRECTION::LEFT_UP)
            && !maskedHLine(map, 4, this->xPos - 32, this->yPos, 32)) {  // No obstacle on the left side
        this->moveDirection = DIRECTION::LEFT;
    }
    else if ((this->currentEnemyDirection == DIRECTION::UP || this->currentEnemyDirection == DIRECTION::LEFT_UP || this->currentEnemyDirection == DIRECTION::RIGHT_UP)
            && !maskedHLine(map, 4, this->xPos - this->width / 2, this->yPos - 33, 32)) {  // No obstacle up
        if (maskedHLine(map, 4, this->xPos, this->yPos - 32, 32)) {  // No obstacle up right
            this->moveDirection = DIRECTION::RIGHT_UP;
        }
        if (maskedHLine(map, 4, this->xPos - 32, this->yPos - 32, 32)) {  // No obstacle up left
            this->moveDirection = DIRECTION::LEFT_UP;
        }
    }

    // Only shoot if there is no wall between
    int oppTileIndex = (int) opp->xPos / 32;
    int botTilePos = (int) this->xPos / 32;
    DIRECTION lpd = DIRECTION::RIGHT;

    if (oppTileIndex > botTilePos) {
        lpd = DIRECTION::RIGHT;
    }
    else { // he base, he bays, but most importantly he BASS
        lpd = DIRECTION::LEFT;
    }

    return true;
}

Bot::~Bot() {}
