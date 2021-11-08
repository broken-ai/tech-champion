#include "config.hpp"

Config::Config() {
}

void Config::parseConfigKey(const std::string& key, const std::string& value) {
	if ("WINDOW_WIDTH" == key) {
		this->WINDOW_WIDTH = std::stoi(value.c_str());

		if (this->WINDOW_WIDTH < 800) {
			this->WINDOW_WIDTH = 800;
		}
	} else if ("WINDOW_HEIGHT" == key) {
		this->WINDOW_HEIGHT = std::stoi(value.c_str());

		if (this->WINDOW_HEIGHT < 600) {
			this->WINDOW_HEIGHT = 600;
		}
	} else if ("FPS_LIMIT" == key) {
		this->FPS_LIMIT = std::stoi(value.c_str());
	} else if ("CHARACTER_SIZE" == key) {
		this->CHARACTER_SIZE = std::stoi(value.c_str());

		if (this->CHARACTER_SIZE < 10) {
			this->CHARACTER_SIZE = 10;
		}

	} else if ("SKIN_FILENAME" == key) {
		this->SKIN_FILENAME = value;
	} else if ("UP" == key) {
		this->UP = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("DOWN" == key) {
		this->DOWN = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("LEFT" == key) {
		this->LEFT = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("RIGHT" == key) {
		this->RIGHT = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("JUMP" == key) {
		this->JUMP = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("SHOOT" == key) {
		this->SHOOT = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("ROLL" == key) {
		this->ROLL = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("AIM_LOCK" == key) {
		this->AIM_LOCK = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("SWITCH_WEAPON" == key) {
		this->SWITCH_WEAPON = (sf::Keyboard::Key)std::stoi(value.c_str());
	} else if ("MASTER_VOLUME" == key) {
		this->MASTER_VOLUME = std::stoi(value.c_str());
	} else if ("SOUND_VOLUME" == key) {
		this->SOUND_VOLUME = std::stoi(value.c_str());
	} else if ("MUSIC_VOLUME" == key) {
		this->MUSIC_VOLUME = std::stoi(value.c_str());
	} else if ("FULLSCREEN" == key) {
		this->FULLSCREEN = (bool)std::stoi(value.c_str());
	}
}

void Config::loadConfig(const std::string& fileName) {
    std::cout << "Loading config from: " << fileName << "\n";

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
				} else {
					value += line[i];
				}
			}

			this->parseConfigKey(key, value);
		}
		infile.close();
	}
}

void Config::save(const std::string& fileName) const {
	std::string data = "";
	std::ofstream configFile;
	configFile.open(fileName);

	data += "WINDOW_WIDTH = " + std::to_string(this->WINDOW_WIDTH) + "\n";
	data += "WINDOW_HEIGHT = " + std::to_string(this->WINDOW_HEIGHT) + "\n";
	data += "FULLSCREEN = " + std::to_string(this->FULLSCREEN) + "\n";
	data += "FPS_LIMIT = " + std::to_string(this->FPS_LIMIT) + "\n";
	data += "CHARACTER_SIZE = " + std::to_string(this->CHARACTER_SIZE) + "\n";
	data += "MASTER_VOLUME = " + std::to_string(this->MASTER_VOLUME) + "\n";
	data += "SOUND_VOLUME = " + std::to_string(this->SOUND_VOLUME) + "\n";
	data += "MUSIC_VOLUME = " + std::to_string(this->MUSIC_VOLUME) + "\n";
	data += "UP = " + std::to_string(this->UP) + "\n";
	data += "DOWN = " + std::to_string(this->DOWN) + "\n";
	data += "LEFT = " + std::to_string(this->LEFT) + "\n";
	data += "RIGHT = " + std::to_string(this->RIGHT) + "\n";
	data += "JUMP = " + std::to_string(this->JUMP) + "\n";
	data += "SHOOT = " + std::to_string(this->SHOOT) + "\n";
	data += "ROLL = " + std::to_string(this->ROLL) + "\n";
	data += "AIM_LOCK = " + std::to_string(this->AIM_LOCK) + "\n";
	data += "SWITCH_WEAPON = " + std::to_string(this->SWITCH_WEAPON) + "\n";

	configFile.write(data.c_str(), data.length());
	configFile.close();
}
