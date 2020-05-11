#include "../../headers/gui/button.hpp"


GUI::Button::Button(const uint16_t &initX, const uint16_t &initY, const std::string &initLabel) {
    this->state = STATE::NORMAL;
    this->xPos = initX;
    this->yPos = initY;
    this->label.setFont(*GAME_FONT);
    this->label.setCharacterSize(g_config.CHARACTER_SIZE);
    this->label.setFillColor(sf::Color::Black);
    this->label.setStyle(sf::Text::Regular);
    this->label.setString(initLabel);
    this->label.setOrigin((int) label.getLocalBounds().width / 2, (int) label.getLocalBounds().height / 2);
    this->label.setPosition(xPos + 48, yPos + 14);

    for (int i = 0; i < 3; ++i) {
        this->sprites[i].setTexture(*GUI_COMMON_TEXTURE);
        this->sprites[i].setTextureRect(sf::IntRect(i * 96, 0, 96, 32));
        this->sprites[i].setPosition(initX, initY);
    }
}

void GUI::Button::updateAndDraw(sf::RenderWindow* inWindow) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*inWindow);

    if (mousePos.x > this->xPos && mousePos.y > this->yPos && mousePos.x < this->xPos + 96 && mousePos.y < this->yPos + 32) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->state = STATE::CLICKED;
        }
        else if (state == STATE::CLICKED) {
            this->state = STATE::RELEASED;
        }
        else {
            this->state = STATE::HOVERED;
        }
    }
    else {
        this->state = STATE::NORMAL;
    }

    if (this->state != STATE::RELEASED) {
        inWindow->draw(this->sprites[(int)state]);
    }
    else {
        inWindow->draw(this->sprites[0]);
    }

    inWindow->draw(label);
}
