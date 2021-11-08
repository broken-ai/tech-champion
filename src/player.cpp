#include "player.hpp"

Player::Player(Config* inConfig, const int& playerID = 0, int startX = 0, int startY = 0) {
	this->xPos = startX;
	this->yPos = startY;
	this->view.reset(sf::FloatRect(0, 0, inConfig->WINDOW_WIDTH, inConfig->WINDOW_HEIGHT));
	this->playerID = playerID;
	this->cameraX = 0;
	this->cameraY = 0;
	//this->invincibility.restart();
	this->hardLandTimer.restart();
	this->direction = 1;
	this->aimAngle = 0;
	this->state = IDLE;
	this->animSet = "player";
}

bool Player::loadSkin(ResourceManager* inRM) {
    std::cout << "[INFO]: Loading player skin.\n";
	this->anim.setSpeed(30);
	return true;
}

playerState Player::idleUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (sf::Keyboard::isKeyPressed(inConfig->LEFT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            return MOVE;
        } else {
            if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 315;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 225;
        else this->aimAngle = 270;
    } else if (sf::Keyboard::isKeyPressed(inConfig->RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            return MOVE;
        } else {
            if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 45;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 135;
        else this->aimAngle = 90;
    } else {
        if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
        else {
            this->xSpeed = 0;
        }

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 0;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 180;
    }

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        if (sf::Keyboard::isKeyPressed(inConfig->JUMP) && this->jumpCount < this->jumpLimit) {
            this->ySpeed = -1 * this->jumpPower;
            this->jumpCount++;
            return JUMP;
        }
    } else return FALL_TRANSITION;

    return IDLE;
}

playerState Player::idleShootUpdate(Config* inConfig, Map* inMap) {

}

playerState Player::moveUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromGroundL = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10); // for vector-based slope detection (lower left corner of collision box)
    int distFromGroundR = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10); // for vector-based slope detection (lower right corner of collision box)
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (sf::Keyboard::isKeyPressed(inConfig->LEFT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed >= -1 * maxHorizontalSpeed) xSpeed -= groundAcc;
            else xSpeed = -1 * maxHorizontalSpeed;

            int temp = maskedTopVLine(inMap, 4, this->xPos - 14, this->yPos + 27, 8);
            if (temp < 8) {
                this->yPos += -4 + temp;
                if (temp < 2) {
                    if (xSpeed < -1 * maxHorizontalSlopeSpeed) xSpeed = -1 * maxHorizontalSlopeSpeed;
                }
            }
        } else {
            if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
            else {
                this->xSpeed = 0;
                return IDLE;
            }
        }

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 315;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 225;
        else this->aimAngle = 270;
    } else if (sf::Keyboard::isKeyPressed(inConfig->RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed <= maxHorizontalSpeed) xSpeed += groundAcc;
            else xSpeed = maxHorizontalSpeed;

            int temp = maskedTopVLine(inMap, 4, this->xPos + 13, this->yPos + 27, 8);
            if (temp < 8) {
                this->yPos += -4 + temp;
                if (temp < 2) {
                    if (xSpeed > maxHorizontalSlopeSpeed) xSpeed = maxHorizontalSlopeSpeed;
                }
            }
        } else {
            /*this->xSpeed = 0;
            return IDLE;*/

            if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
            else {
                this->xSpeed = 0;
                return IDLE;
            }
        }

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 45;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 135;
        else this->aimAngle = 90;
    } else {
        //this->xSpeed = 0;
        //return IDLE;
        if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
        else {
            this->xSpeed = 0;
            return IDLE;
        }
    }

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        if (sf::Keyboard::isKeyPressed(inConfig->JUMP) && this->jumpCount < this->jumpLimit) {
            this->ySpeed = -1 * this->jumpPower;
            this->jumpCount++;
            return JUMP;
        }
    } else return FALL_TRANSITION;

    return MOVE;
}

playerState Player::moveShootUpdate(Config* inConfig, Map* inMap) {

}

playerState Player::jumpUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (sf::Keyboard::isKeyPressed(inConfig->LEFT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed >= -1 * maxHorizontalSpeed) xSpeed -= airAcc;
            else xSpeed = -1 * maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 315;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 225;
        else this->aimAngle = 270;
    } else if (sf::Keyboard::isKeyPressed(inConfig->RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed <= maxHorizontalSpeed) xSpeed += airAcc;
            else xSpeed = maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 45;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 135;
        else this->aimAngle = 90;
    } else {
        //this->xSpeed = 0;
        if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
        else {
            this->xSpeed = 0;
        }
    }

    if (this->ySpeed < 0 && this->jumpCount > 0 && !sf::Keyboard::isKeyPressed(inConfig->JUMP)) this->ySpeed /= 1.5; // control height of jump by releasing jump key

    if (distFromCeiling > -10 && distFromCeiling >= this->ySpeed) {
        this->ySpeed = 1;
        this->yPos += distFromCeiling;
        return FALL_TRANSITION;
    }

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        this->yPos += distFromGround;
        this->ySpeed = 0;
        this->jumpCount = 0;
        return LAND;
    } else {
        if (this->ySpeed > -1) return FALL_TRANSITION;

        if (this->ySpeed < 20) this->ySpeed += GRAVITY_CONST;
    }

    return JUMP;
}

playerState Player::jumpShootUpdate(Config* inConfig, Map* inMap) {

}

playerState Player::fallTransitionUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (sf::Keyboard::isKeyPressed(inConfig->LEFT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed >= -1 * maxHorizontalSpeed) xSpeed -= airAcc;
            else xSpeed = -1 * maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 315;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 225;
        else this->aimAngle = 270;
    } else if (sf::Keyboard::isKeyPressed(inConfig->RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed <= maxHorizontalSpeed) xSpeed += airAcc;
            else xSpeed = maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 45;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 135;
        else this->aimAngle = 90;
    } else {
        //this->xSpeed = 0;
        if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
        else {
            this->xSpeed = 0;
        }
    }

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        this->yPos += distFromGround;
        this->ySpeed = 0;
        this->jumpCount = 0;
        return LAND;
    } else if (this->ySpeed < 20) this->ySpeed += GRAVITY_CONST;

    if (this->anim.getFrame() >= 5) return FALL;

    return FALL_TRANSITION;
}

playerState Player::fallUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (sf::Keyboard::isKeyPressed(inConfig->LEFT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed >= -1 * maxHorizontalSpeed) xSpeed -= airAcc;
            else xSpeed = -1 * maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : -1 * airDec;
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = -1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 315;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 225;
        else this->aimAngle = 270;
    } else if (sf::Keyboard::isKeyPressed(inConfig->RIGHT)) {
        if (!sf::Keyboard::isKeyPressed((inConfig->AIM_LOCK))) {
            if (xSpeed <= maxHorizontalSpeed) xSpeed += airAcc;
            else xSpeed = maxHorizontalSpeed;
        } else {
            //this->xSpeed = 0;

            if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
            else {
                this->xSpeed = 0;
            }
        }

        this->direction = 1;

        if (sf::Keyboard::isKeyPressed(inConfig->UP)) this->aimAngle = 45;
        else if (sf::Keyboard::isKeyPressed(inConfig->DOWN)) this->aimAngle = 135;
        else this->aimAngle = 90;
    } else {
        //this->xSpeed = 0;
        if (this->xSpeed <= -1 * airDec || this->xSpeed >= airDec) this->xSpeed += this->xSpeed < 0 ? airDec : (-1 * airDec);
        else {
            this->xSpeed = 0;
        }
    }

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
        this->yPos += distFromGround;
        this->jumpCount = 0;
        if (this->ySpeed >= 17) {
            this->ySpeed = 0;
            this->hardLandTimer.restart();
            return HARD_LAND;
        } else {
            this->ySpeed = 0;
            return LAND;
        }
    } else if (this->ySpeed < 20) this->ySpeed += GRAVITY_CONST;

    return FALL;
}

playerState Player::fallShootUpdate(Config* inConfig, Map* inMap) {

}

playerState Player::landUpdate(Config* inConfig, Map* inMap) {
    return IDLE;
}

playerState Player::hardLandUpdate(Config* inConfig, Map* inMap) {
    int distFromGround = maskedTopVArea(inMap, 4, this->xPos - 14, this->yPos + 31, this->width - 4, 10);
    int distFromCeiling = maskedTopVArea(inMap, 4, this->xPos - 16, this->yPos - 32, this->width, -10);

    if (this->xSpeed <= -1 * groundDec || this->xSpeed >= groundDec) this->xSpeed += this->xSpeed < 0 ? groundDec : (-1 * groundDec);
    else this->xSpeed = 0;

    if (distFromGround < 10 && distFromGround <= this->ySpeed) {
    } else return FALL_TRANSITION;

    if (this->hardLandTimer.getElapsedTime().asMilliseconds() >= 1000) return IDLE;

    return HARD_LAND;
}

void Player::update(Config* inConfig, Map* inMap) {
    switch(this->state) {
    case IDLE:
        this->state = this->idleUpdate(inConfig, inMap);
        break;
    case IDLE_SHOOT:
        this->state = this->idleShootUpdate(inConfig, inMap);
        break;
    case MOVE:
        this->state = this->moveUpdate(inConfig, inMap);
        break;
    case MOVE_SHOOT:
        this->state = this->moveShootUpdate(inConfig, inMap);
        break;
    case JUMP:
        this->state = this->jumpUpdate(inConfig, inMap);
        break;
    case JUMP_SHOOT:
        this->state = this->jumpShootUpdate(inConfig, inMap);
        break;
    case FALL_TRANSITION:
        this->state = this->fallTransitionUpdate(inConfig, inMap);
        break;
    case FALL:
        this->state = this->fallUpdate(inConfig, inMap);
        break;
    case FALL_SHOOT:
        this->state = this->fallShootUpdate(inConfig, inMap);
        break;
    case LAND:
        this->state = this->landUpdate(inConfig, inMap);
        break;
    case HARD_LAND:
        this->state = this->hardLandUpdate(inConfig, inMap);
        break;
    }

	int lWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos - 10, this->yPos - 30, -8, this->height - 9);
	int rWallIntrusion = maskedFirstHArea(inMap, 4, this->xPos + 9, this->yPos - 30, 8, this->height - 9);

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
	this->cameraX = this->xPos - inConfig->WINDOW_WIDTH / 2;
	this->cameraY = this->yPos - inConfig->WINDOW_HEIGHT / 2;
	this->view.setCenter(this->cameraX + inConfig->WINDOW_WIDTH / 2, this->cameraY + inConfig->WINDOW_HEIGHT / 2);

	// Shooting in the player's aim direction
	/*if (!this->shootHeld && sf::Keyboard::isKeyPressed(g_config.SHOOT)) {
		bullets.push_back(new BasicBullet(this->xPos, this->yPos, this->aimAngle, this->playerID));
	}

	//shootHeld = sf::Keyboard::isKeyPressed(g_config.SHOOT);*/
}

void Player::draw(ResourceManager* inRM, sf::RenderWindow* window) {
	switch(this->state) {
    case IDLE:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[0], this->direction, 1, true, window);
        break;
    case MOVE:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[1], this->direction, 1, true, window);
        break;
    case JUMP:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[2], this->direction, 1, true, window);
        break;
    case FALL_TRANSITION:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[3], this->direction, 1, true, window);
        break;
    case FALL:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[4], this->direction, 1, true, window);
        break;
    case LAND:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[5], this->direction, 1, true, window);
        break;
    case HARD_LAND:
        this->anim.play(this->xPos, this->yPos, inRM->animSets[inRM->getAnimSet(this->animSet)]->animations[6], this->direction, 1, true, window);
        break;
	}
}

Player::~Player() {
}
