#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include "base.hpp"

class Config {
	/**
    Config class, if not loaded, it contains the built-in settings
    */
public:
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;
	int FPS_LIMIT = 60;
	int CHARACTER_SIZE = 14;
	std::string playerName = "Player";				   // player name
	std::string SKIN_FILENAME = "content/default.png"; // selected player skin

	/**
    Keyboard configuration
    name = KEY_LABELS.INDEX
    */
	sf::Keyboard::Key UP = sf::Keyboard::Up;
	sf::Keyboard::Key DOWN = sf::Keyboard::Down;
	sf::Keyboard::Key LEFT = sf::Keyboard::Left;
	sf::Keyboard::Key RIGHT = sf::Keyboard::Right;
	sf::Keyboard::Key JUMP = sf::Keyboard::S;
	sf::Keyboard::Key SHOOT = sf::Keyboard::D;
	sf::Keyboard::Key ROLL = sf::Keyboard::W;
	sf::Keyboard::Key AIM_LOCK = sf::Keyboard::A;
	sf::Keyboard::Key SWITCH_WEAPON = sf::Keyboard::Q;

	int MASTER_VOLUME = 100;
	int SOUND_VOLUME = 100;
	int MUSIC_VOLUME = 100;
	bool FULLSCREEN = false;

	Config();

	/**
    Loads configuration from the given filename to
    the config pointer.
    */
	void loadConfig(const std::string& fileName);

	/**
    Saves configuration to the "BASE_FOLDER + config.ini" file
    */
	void save(const std::string& fileName) const;

private:
	/**
    Setting the "config" struct variable "key" to the given "value"
    */
	void parseConfigKey(const std::string& key, const std::string& value);
};

#endif // _CONFIG_HPP_
