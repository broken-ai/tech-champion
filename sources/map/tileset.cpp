#include "../../headers/map/tileset.hpp"


Tileset::Tileset() {}

void Tileset::initialize(const std::string &filepath) {
    PHYSFS_addToSearchPath(filepath.c_str(), 1);
    PhysFsStream tctStream;

    // Loading image
    tctStream.open("image.png");
    this->texture.loadFromStream(tctStream);
    tctStream.close();
    sf::Vector2u imgSize = this->texture.getSize();

    // Loading mask
    unsigned int bufferSize = (imgSize.x + 2) * imgSize.y;
    char buffer[bufferSize];
    tctStream.open("mask.msk");
    tctStream.read(buffer, bufferSize);
    tctStream.close();

    // Convert buffer to boolean mask
    std::vector<bool> maskRow;

    for (unsigned int i = 0; i < bufferSize; i++) {
        if (buffer[i] == '\n' && maskRow.size() != 0) {
            this->mask.push_back(maskRow);
            maskRow.clear();
        }

        if (buffer[i] == '0' || buffer[i] == '1') {
            maskRow.push_back(buffer[i] == '1');
        }
    }

    for (unsigned int j = 0; j < (unsigned int)(imgSize.y / 32); j++) {
        for (unsigned int i = 0; i < 10; i++) {
            this->tileSprites.push_back(sf::Sprite(this->texture, sf::IntRect(i * 32, j * 32, 32, 32)));
        }
    }
    PHYSFS_removeFromSearchPath(filepath.c_str());
}

Tileset::~Tileset() {
    delete &this->texture;
    delete &this->mask;
    delete &this->tileSprites;
}
