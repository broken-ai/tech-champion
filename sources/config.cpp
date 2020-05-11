#include "../headers/config.hpp"


Config::Config() {}

const void Config::parseConfigKey(const std::string &key, const std::string &value) {
    if ("WINDOW_WIDTH" == key) {
        try {
            this->WINDOW_WIDTH = std::stoi(value.c_str());

            if (this->WINDOW_WIDTH < 800) {
                this->WINDOW_WIDTH = 800;
            }
        } catch (std::exception) {}
    }
    else if ("WINDOW_HEIGHT" == key) {
        try {
            this->WINDOW_HEIGHT = std::stoi(value.c_str());

            if (this->WINDOW_HEIGHT < 600) {
                this->WINDOW_HEIGHT = 600;
            }
        } catch (std::exception) {}
    }
    else if ("FPS_LIMIT" == key) {
        try {
            this->FPS_LIMIT = std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("CHARACTER_SIZE" == key) {
        try {
            this->CHARACTER_SIZE = std::stoi(value.c_str());

            if (this->CHARACTER_SIZE < 10) {
                this->CHARACTER_SIZE = 10;
            }

        } catch (std::exception) {}
    }
    else if ("SKIN_FILENAME" == key) {
        try {
            this->SKIN_FILENAME = value;
        } catch (std::exception) {}
    }
    else if ("UP" == key) {
        try {
            this->UP = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("DOWN" == key) {
        try {
            this->DOWN = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("LEFT" == key) {
        try {
            this->LEFT = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("RIGHT" == key) {
        try {
            this->RIGHT = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("JUMP" == key) {
        try {
            this->JUMP = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("SHOOT" == key) {
        try {
            this->SHOOT = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("ROLL" == key) {
        try {
            this->ROLL = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("AIM_LOCK" == key) {
        try {
            this->AIM_LOCK = (sf::Keyboard::Key) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("MASTER_VOLUME" == key) {
        try {
            this->MASTER_VOLUME = std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("SOUND_VOLUME" == key) {
        try {
            this->SOUND_VOLUME = std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("MUSIC_VOLUME" == key) {
        try {
            this->MUSIC_VOLUME = std::stoi(value.c_str());
        } catch (std::exception) {}
    }
    else if ("FULLSCREEN" == key) {
        try {
            this->FULLSCREEN = (bool) std::stoi(value.c_str());
        } catch (std::exception) {}
    }
}

const void Config::loadConfig(const std::string &fileName) {
    std::ifstream infile(fileName);
    std::string line;

    // Start reading from file
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::string key;
            std::string value;
            bool parseKey = true;

            // Parse each line char by char
            for (uint8_t i = 0; i < line.length(); i++) {
                if (line[i] == ' ') {
                    continue;
                }

                if (line[i] == '=') {
                    parseKey = false;
                    continue;
                }

                if (parseKey) {
                    key += line[i];
                }
                else {
                    value += line[i];
                }
            }

            this->parseConfigKey(key, value);
        }
        infile.close();
    }
}

const void Config::save(const std::string &fileName) const {
    std::string data = "";
    std::ofstream configFile;
    configFile.open(fileName);

    data += "WINDOW_WIDTH = " + Utils::to_string(this->WINDOW_WIDTH) + "\n";
    data += "WINDOW_HEIGHT = " + Utils::to_string(this->WINDOW_HEIGHT) + "\n";
    data += "FPS_LIMIT = " + Utils::to_string(this->FPS_LIMIT) + "\n";
    data += "CHARACTER_SIZE = " + Utils::to_string(this->CHARACTER_SIZE) + "\n";
    data += "UP = " + Utils::to_string(this->UP) + "\n";
    data += "DOWN = " + Utils::to_string(this->DOWN) + "\n";
    data += "LEFT = " + Utils::to_string(this->LEFT) + "\n";
    data += "RIGHT = " + Utils::to_string(this->RIGHT) + "\n";
    data += "JUMP = " + Utils::to_string(this->JUMP) + "\n";
    data += "SHOOT = " + Utils::to_string(this->SHOOT) + "\n";
    data += "ROLL = " + Utils::to_string(this->ROLL) + "\n";
    data += "AIM_LOCK = " + Utils::to_string(this->AIM_LOCK) + "\n";
    data += "MASTER_VOLUME = " + Utils::to_string(this->MASTER_VOLUME) + "\n";
    data += "SOUND_VOLUME = " + Utils::to_string(this->SOUND_VOLUME) + "\n";
    data += "MUSIC_VOLUME = " + Utils::to_string(this->MUSIC_VOLUME) + "\n";
    data += "FULLSCREEN = " + Utils::to_string(this->FULLSCREEN) + "\n";

    configFile.write(data.c_str(), data.length());
    configFile.close();
}
