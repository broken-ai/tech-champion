#include "../headers/animation.hpp"
#include "../headers/anim_set.hpp"
#include "../headers/resource_manager.hpp"


ResourceManager::ResourceManager() {
    this->isLoaded = false;
}

const bool ResourceManager::load() {
    if (this->isLoaded) return true;

    // g_rm.animSets.push_back(new AnimSet(BASE_FOLDER + "media/animations/akarmi.tca", g_rm.animTextures));
    // g_rm.animSets.push_back(new AnimSet(BASE_FOLDER + "media/animations/player.tca", g_rm.animTextures));

    // Load all animations form the animations directory
    for (std::string fileName : Utils::listdir(BASE_FOLDER + ANIMATION_FOLDER)) {
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
        g_rm.animSets.push_back(new AnimSet(BASE_FOLDER + ANIMATION_FOLDER + fileName, g_rm.animTextures, fileName.substr(0, fileName.length() - 4)));
    }

    this->isLoaded = true;
    return true;
}

const Animation ResourceManager::getAnim(const std::string &animSetName, const int &animIndex) {
    for (AnimSet* animSet : this->animSets) {
        if (animSet->name == animSetName) {
            return animSet->animations[animIndex];
        }
    }

    openMessageBox("ERROR: Can't load animset for name: " + animSetName);
}

const void ResourceManager::update() {
    for (size_t i = 0; i < this->bullets.size(); i++) {
        if (this->bullets[i]->lifeTimeCounter > BasicBullet::maxLifeTime) {
            this->bullets.erase(this->bullets.begin() + i);
            continue;
        }
    }
}
