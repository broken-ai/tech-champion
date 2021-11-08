#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "config.hpp"
#include "resource_manager.hpp"

#define groundAcc 0.3               // acceleration on the ground
#define groundDec 0.3               // deceleration on the ground
#define airAcc 0.2                  // acceleration in the air
#define airDec 0.07                 // deceleration in the air
#define maxHorizontalSpeed 6        // maximum movement speed on level ground
#define maxHorizontalSlopeSpeed 4   // maximum movement speed


enum playerState {
    IDLE,               // standing still, doing nothing
    IDLE_SHOOT,         // shooting while standing still
    MOVE,               // moving while on the ground
    MOVE_SHOOT,         // shooting while moving on the ground
    JUMP,               // jumping into the air either from idle position or moving
    JUMP_SHOOT,         // shooting while in jump state
    FALL_TRANSITION,    // transitioning from 0 vertical speed to falling
    FALL,               // falling from a jump or a ledge
    FALL_SHOOT,         // shooting while falling
    LAND,               // landing from a fall
    HARD_LAND,          // landing from a fall with high vertical speed, getting stunned for a second
    SLIDE,              // sliding down on a steep slope
    ROLL                // rolling forward on the ground
};

class Player {
public:
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
	const uint8_t width = 32;  // collision box width in pixels (animation can be wider)
	const uint8_t height = 64; // collision box height in pixels (animation can be taller)
	int8_t direction;		   // direction the player is facing (-1 for left, 1 for right)
	uint16_t aimAngle;		   // the angle projectiles will be shot, in degrees (0 is straight up)
	uint8_t jumpPower = 12;
	uint8_t jumpLimit = 1;
	uint8_t jumpCount = 0;
	uint8_t health;
	//sf::Clock invincibility; // remaining duration of invincibility (eg. after respawning)
	sf::Clock hardLandTimer; // remaining time until the player can move again after a hard landing
	playerState state; // which state the player is currently in (idle, moving, jumping, etc.)
	std::string animSet; // which animation set the player is using ()
	AnimPlayer anim; // this grabs frames from loaded animation sets, and plays animations

	sf::View view;
	uint8_t playerID; // used for identification in servers, aka. player number
	int cameraX;
	int cameraY;

	Player(Config* inConfig, const int& playerID, int initX, int initY);
	~Player();
	bool loadSkin(ResourceManager* inRM);
	playerState idleUpdate(Config* inConfig, Map* inMap);
    playerState idleShootUpdate(Config* inConfig, Map* inMap);
    playerState moveUpdate(Config* inConfig, Map* inMap);
    playerState moveShootUpdate(Config* inConfig, Map* inMap);
    playerState jumpUpdate(Config* inConfig, Map* inMap);
    playerState jumpShootUpdate(Config* inConfig, Map* inMap);
    playerState fallTransitionUpdate(Config* inConfig, Map* inMap);
    playerState fallUpdate(Config* inConfig, Map* inMap);
    playerState fallShootUpdate(Config* inConfig, Map* inMap);
    playerState landUpdate(Config* inConfig, Map* inMap);
    playerState hardLandUpdate(Config* inConfig, Map* inMap);
    void update(Config* inConfig, Map* inMap);
	void draw(ResourceManager* inRM, sf::RenderWindow* window);
};

#endif // _PLAYER_HPP_
