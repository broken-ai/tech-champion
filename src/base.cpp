#include "base.hpp"

//sf::Font* GAME_FONT = new sf::Font(); // moved to resource manager
sf::Texture* GUI_COMMON_TEXTURE = new sf::Texture();

/**
    @returns true if the given file exists
    */
bool Utils::doesFileExist(std::string fileName) { // replace by std::filesystem::exists() ??
	std::ifstream infile(fileName);
	return infile.good();
}

/**
    Parses the current working directory from the exeFilePath parameter.
    */
void Utils::setBaseDir(std::string& toSet, std::string exeFilePath) {
	/*uint8_t lastSlashIndex = 0;

	for (uint8_t i = 0; i < exeFilePath.length(); i++) {
		if (exeFilePath[i] == '\\' || exeFilePath[i] == '/') {
			lastSlashIndex = i;
		}
	}

	toSet = exeFilePath.substr(0, lastSlashIndex + 1);*/
	toSet = std::filesystem::current_path().string();
}

template <typename T>
std::string Utils::to_string(const T& n) {
	std::ostringstream stm;
	stm << n;
	return stm.str();
}
