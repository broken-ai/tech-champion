#include "animation.hpp"

Animation::Animation() {
	this->frameCount = 0;
	this->width = 0;
	this->height = 0;
}

Animation::~Animation() {
}


AnimSet::AnimSet() {
}

AnimSet::AnimSet(std::string filepath, std::string name) {
    if (!std::filesystem::exists(filepath)) {
        std::cout << "[ERROR]: Animation set file does not exist. (" << filepath << ")\n  Trying to play animations from this set will most likely cause the game to crash.\n";
        return; // don't even try to load the file, if it doesn't exist
    }

	this->name = name;

	// Load animation set from file
	PHYSFS_mount(filepath.c_str(), "", 1);
	PhysFsStream tcaStream;

	uint16_t numOfAnims = 0; //number of animations inside the animation set file, given value from a text file inside
	int tempFrames = 0;		 //to be read from <number>.adt
	int tempWidth = 0;		 //to be read from <number>.adt
	int tempHeight = 0;		 //to be read from <number>.adt

	const int animNumBufferSize = 3;
	char animNumData[animNumBufferSize];

	tcaStream.open("num_of_anims.txt");
	tcaStream.read(animNumData, animNumBufferSize);
	tcaStream.close();
	numOfAnims = std::atoi(animNumData);

	// Loading animation images
	for (int i = 0; i < numOfAnims; i++) {
		this->animations.push_back(Animation());

		tcaStream.open((std::to_string(i) + ".png").c_str());
		this->animations.back().texture.loadFromStream(tcaStream);
		tcaStream.close();

		const int bufferSize = 64;
		char buffer[bufferSize];


		tcaStream.open((std::to_string(i) + ".adt").c_str());
		tcaStream.read(buffer, bufferSize);
		tcaStream.close();

		// Reading variables from buffer
		//std::string strBuffer = std::to_string(buffer);
		std::string strBuffer(buffer);
		std::string key = "", value = "";
		bool inKey = true;

		for (unsigned int pos = 0; pos < strBuffer.length(); pos++) {
			if (strBuffer[pos] == ' ' || strBuffer[pos] == '\t')
				continue;
			if (strBuffer[pos] == '=') {
				inKey = false;
				continue;
			}
			if (!inKey && strBuffer[pos] == '\n') {
				if (key == "frames") {
					tempFrames = std::stoi(value.c_str());
				} else if (key == "frameWidth") {
					tempWidth = std::stoi(value.c_str());
				} else if (key == "frameHeight") {
					tempHeight = std::stoi(value.c_str());
				}
				key = "";
				value = "";
				inKey = true;
				continue;
			}

			if (inKey) {
				key += strBuffer[pos];
			} else {
				value += strBuffer[pos];
			}
		}

		this->animations.back().frameCount = tempFrames;
		this->animations.back().width = tempWidth;
		this->animations.back().height = tempHeight;
	}
	PHYSFS_unmount(filepath.c_str());

	std::cout << "[INFO]: Animation set \"" << this->name << "\" successfully loaded.\n";
}

AnimSet::~AnimSet() {
}

AnimPlayer::AnimPlayer() {
    this->speed = 1;
	this->curFrame = 0;
	this->flipped = false;
	this->counter.restart();
}

AnimPlayer::~AnimPlayer() {
}

void AnimPlayer::reset() {
	this->curFrame = 0;
	this->counter.restart();
}

void AnimPlayer::play(const int& xPos, const int& yPos, const Animation& animation, const int8_t& directionH, const int8_t& directionV, const bool& draw, sf::RenderWindow* inWindow = nullptr) {
    if (this->sprite.getTexture() != &animation.texture) {
        this->sprite.setTexture(animation.texture);
        this->sprite.setOrigin(animation.width / 2, animation.height / 2);
    }

    this->sprite.setPosition(xPos, yPos);
    this->sprite.setScale(directionH, directionV);

	if (this->speed > 0) {
		if (this->counter.getElapsedTime().asMilliseconds() >= (1000 / this->speed)) {
			if (this->curFrame < animation.frameCount - 1) curFrame++;
			else curFrame = 0;

			this->counter.restart();
		}

		this->sprite.setTextureRect(sf::IntRect(curFrame * animation.width, 0, animation.width, animation.height));
	}

	if (draw && inWindow != nullptr) {
		inWindow->draw(this->sprite);
	}
}

void AnimPlayer::setSpeed(const unsigned int& speed) {
	if (speed > 0 && speed < 999) {
        this->speed = speed;
	}
}

int AnimPlayer::getFrame() {
    return this->curFrame;
}

void AnimPlayer::setFrame(const unsigned int& frame) {
	this->curFrame = frame;
}
