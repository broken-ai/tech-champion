#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include "animation.hpp"
#include "map.hpp"

class ResourceManager {
/**
    Loads and manages images, animations, music and sound
*/

public:
	bool isLoaded;
	sf::Font menuFont; // font for the main menu and settings menu
	sf::Text menuText;
	//sf::Font hudFont; // font for the in-game HUD
	//sf::Font playerFont; // font for player names in-game
	//sf::Font consoleFont; // font for the debug console and chat
	std::vector<AnimSet*> animSets;

	ResourceManager();
	bool load(std::string inPath);
	uint16_t getAnimSet(std::string animSetName);
	//Animation getAnim(std::string animSetName, int animIndex);
	//void update();
};

#endif // _RESOURCE_MANAGER_HPP_
