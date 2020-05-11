#include "../headers/anim_set.hpp"


AnimSet::AnimSet() {}

AnimSet::AnimSet(const std::string &filepath, std::vector<sf::Texture*> animTextures, const std::string &name) {
    this->name = name;

    // Load animation set from file
    PHYSFS_addToSearchPath(filepath.c_str(), 1);
    PhysFsStream tcaStream;

    uint16_t numOfAnims; //number of animations inside the animation set file, given value from a text file inside
    int tempFrames; //to be read from <number>.adt
    int tempWidth; //to be read from <number>.adt
    int tempHeight; //to be read from <number>.adt

    const int animNumBufferSize = 3;
    char animNumData[animNumBufferSize];

    tcaStream.open("anim_num.txt");
    tcaStream.read(animNumData, animNumBufferSize);
    tcaStream.close();
    numOfAnims = std::atoi(animNumData);

    // Loading animation images
    for (int i = 0; i < numOfAnims; i++) {
        animTextures.push_back(new sf::Texture());

        tcaStream.open((Utils::to_string(i) + ".png").c_str());
        animTextures.back()->loadFromStream(tcaStream);
        tcaStream.close();

        const int bufferSize = 64;
        char buffer[bufferSize];

        this->animations.push_back(Animation());
        tcaStream.open((Utils::to_string(i) + ".adt").c_str());
        tcaStream.read(buffer, bufferSize);
        tcaStream.close();

        // Reading variables from buffer
        std::string strBuffer = Utils::to_string(buffer);
        std::string key = "", value = "";
        bool inKey = true;

        for (int pos = 0; pos < strBuffer.length(); pos++) {
            if (strBuffer[pos] == ' ' || strBuffer[pos] == '\t') continue;
            if (strBuffer[pos] == '=') {
                inKey = false;
                continue;
            }
            if (!inKey && strBuffer[pos] == '\n') {
                if (key == "frames") {
                    tempFrames = std::stoi(value.c_str());
                }
                else if (key == "frameWidth") {
                    tempWidth = std::stoi(value.c_str());
                }
                else if (key == "frameHeight") {
                    tempHeight = std::stoi(value.c_str());
                }
                key = "";
                value = "";
                inKey = true;
                continue;
            }

            if (inKey) {
                key += strBuffer[pos];
            }
            else {
                value += strBuffer[pos];
            }
        }

        this->animations.back().frameCount = tempFrames;
        this->animations.back().width = tempWidth;
        this->animations.back().height = tempHeight;

        for (int j = 0; j < tempFrames; j++) { //adding frames to the current animation in the animation set
            this->animations.back().frames.push_back(sf::Sprite(*animTextures.back(), sf::IntRect(j * tempWidth, 0, tempWidth, tempHeight)));
            this->animations.back().frames.back().setOrigin(tempWidth / 2, tempHeight / 2);
        }
    }
    PHYSFS_removeFromSearchPath(filepath.c_str());
}

AnimSet::~AnimSet() {}
