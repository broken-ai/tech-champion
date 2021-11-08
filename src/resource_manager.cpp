#include "resource_manager.hpp"

ResourceManager::ResourceManager() {
	this->isLoaded = false;
}

bool ResourceManager::load(std::string inPath) {
	if (this->isLoaded) return true; // if the contents of this instance of this class have already been loaded, don't do anything but return success

	if (!this->menuFont.loadFromFile(inPath + "\\content\\font\\FreeMonospacedBold.ttf")) {
        std::cout << "[ERROR]: Can't open game font.\n";
        return EXIT_FAILURE;
    }

    this->menuText = sf::Text("", this->menuFont);
    this->menuText.setCharacterSize(24);
    this->menuText.setFillColor(sf::Color::White);
    this->menuText.setStyle(sf::Text::Regular);
    this->menuText.setPosition(0, 0);

	this->animSets.push_back(new AnimSet(inPath + "\\content\\animations\\playerDebug_dummy.tca", "player"));

	// Load all animations from the animations directory
	/*for (std::string fileName : Utils::listdir(BASE_FOLDER + ANIMATION_FOLDER)) {
		if (fileName == "." || fileName == "..") {
			continue;
		}

		std::string extension = "";
		bool inExtension = false;

		for (uint8_t i = 0; i < fileName.length(); i++) {
			if (fileName[i] == '.') {
				inExtension = true;
				continue;
			}

			if (inExtension) {
				extension += fileName[i];
			}
		}

		if (!inExtension) {
			continue;
		}
		this->animSets.push_back(new AnimSet(BASE_FOLDER + ANIMATION_FOLDER + fileName, this->animTextures, fileName.substr(0, fileName.length() - 4)));
	}*/

	this->isLoaded = true;
	return true;
}

uint16_t ResourceManager::getAnimSet(std::string animSetName) { // gets the index of the AnimSet in the resource manager, matching the given name
    for (uint16_t i = 0; i < this->animSets.size(); i++) {
        if (this->animSets[i]->name == animSetName) return i;
    }

    std::cout << "[ERROR]: no AnimSet with the name \"" + animSetName + "\" found.\n";
    return 0;
}

/*Animation ResourceManager::getAnim(std::string animSetName, int animIndex) {
    std::cout << "[INFO]: getAnim() called.\n";
	for (AnimSet* animSet : this->animSets) {
		if (animSet->name == animSetName) {
            std::cout << "[getAnim]: Returning animation found.\n";
			return animSet->animations[animIndex];
		}
	}

	Animation failAnim;

    std::cout << "[getAnim]: Returning failAnim.\n";
	return failAnim;

	//openMessageBox("ERROR: Can't load animset for name: " + animSetName);
}*/
