#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

class Config {
    /**
    Config class, at if not loaded then it contains the basic built-in settings
    */
public:
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
    int FPS_LIMIT = 60;
    int CHARACTER_SIZE = 14;
    std::string SKIN_FILENAME = "media/base.png";

    /**
    Keyboard configuration
    name = KEY_LABELS.INDEX
    */
    sf::Keyboard::Key UP = sf::Keyboard::W;
    sf::Keyboard::Key DOWN = sf::Keyboard::S;
    sf::Keyboard::Key LEFT = sf::Keyboard::A;
    sf::Keyboard::Key RIGHT = sf::Keyboard::D;
    sf::Keyboard::Key JUMP = sf::Keyboard::Space;
    sf::Keyboard::Key SHOOT = sf::Keyboard::T;
    sf::Keyboard::Key ROLL = sf::Keyboard::T;
    sf::Keyboard::Key AIM_LOCK = sf::Keyboard::T;

    int MASTER_VOLUME = 100;
    int SOUND_VOLUME = 100;
    int MUSIC_VOLUME = 100;
    bool FULLSCREEN = false;


    Config();

    /**
    Loads configuration from the given filename to
    the config pointer.
    */
    const void loadConfig(const std::string &fileName);

    /**
    Saves configuration to the "BASE_FOLDER + config.ini" file
    */
    const void save(const std::string &fileName) const;

private:
    /**
    Setting the "config" struct variable "key" to the given "value"
    */
    const void parseConfigKey(const std::string &key, const std::string &value);
};

// Define configuration as a global variable
Config g_config;

#endif // _CONFIG_HPP_
