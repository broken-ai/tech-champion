#include "../../headers/gui/slider.hpp"


Slider::Slider(const uint16_t &xPos, const uint16_t &yPos) {
	this->xCord = xPos;
	this->yCord = yPos;
	this->axisHeight = 20;
	this->axisWidth = 200;
	this->sliderWidth = 20;
	this->sliderHeight = 20;

	this->text.setFont(*GAME_FONT);
	this->text.setFillColor(sf::Color::White);

	this->axis.setPosition(xPos, yPos);
	this->axis.setOrigin(0, this->axisHeight / 2);
	this->axis.setSize(sf::Vector2f(this->axisWidth, this->axisHeight));
	this->axis.setFillColor(sf::Color(63, 63, 63));
	this->slider.setPosition(xPos, yPos);
	this->slider.setOrigin(this->sliderWidth / 2, this->sliderHeight / 2);
	this->slider.setSize(sf::Vector2f(this->sliderWidth, this->sliderHeight));
	this->slider.setFillColor(sf::Color(192, 192, 192));
}

const sf::Text Slider::returnText(const uint16_t &x, const uint16_t &y, const std::string &z, const uint8_t &fontSize) {
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(x, y);
	this->text.setString(z);
	return text;
}

const void Slider::create(const uint16_t &min, const uint16_t &max) {
	this->sliderValue = min;
	this->minValue = min;
	this->maxValue = max;
}

const void Slider::setSliderValue(const float &newValue) {
	if (newValue >= this->minValue && newValue <= this->maxValue) {
		this->sliderValue = newValue;
		const float diff = this->maxValue - this->minValue;
		const float diff2 = newValue - this->minValue;
		const float zzz = this->axisWidth / diff;
		float posX = zzz * diff2;
		posX += this->xCord;
		slider.setPosition(posX, this->yCord);
	}
}

const void Slider::setSliderPercentValue(const float &newPercentValue) {
	if (newPercentValue >= 0 && newPercentValue <= 100) {
		this->sliderValue = newPercentValue / 100 * this->maxValue;
		this->slider.setPosition(this->xCord + (this->axisWidth * newPercentValue / 100), this->yCord);
	}
}

void Slider::updateAndDraw(sf::RenderWindow *window) {
	sf::Vector2i mpos = sf::Mouse::getPosition(*window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
            this->axis.getGlobalBounds().contains(mpos.x, mpos.y)) {
        this->slider.setPosition(mpos.x, this->yCord);
        this->sliderValue = (this->minValue + ((this->slider.getPosition().x - this->xCord) / this->axisWidth * (this->maxValue - this->minValue)));

        if (this->sliderValue >= 98) {
            this->sliderValue = 100;
        }
    }

	window->draw(this->axis);
	window->draw(this->slider);
	window->draw(this->returnText(this->xCord + this->axisWidth + 10, this->yCord - 10,
                                    Utils::to_string((int) this->sliderValue),
                                    g_config.CHARACTER_SIZE));
}

Slider::~Slider() {
    delete &this->slider;
	delete &this->axis;
	delete &this->text;
	delete &this->minValue;
	delete &this->maxValue;
	delete &this->xCord;
	delete &this->yCord;
	delete &this->axisWidth;
	delete &this->axisHeight;
	delete &this->sliderWidth;
	delete &this->sliderHeight;
	delete &this->sliderValue;
}
