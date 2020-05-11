#include "../../headers/gui/check_box.hpp"


GUI::Checkbox::Checkbox(const uint16_t &initX, const uint16_t &initY, const std::string &initLabel, const bool &lLeft) {
    uint8_t textW, textH;

    this->buttonHeld = false;
    this->checkState = CHECK_STATE::UNCHECKED;
    this->xPos = initX;
    this->yPos = initY;
    this->label.setFont(*GAME_FONT);
    this->label.setCharacterSize(g_config.CHARACTER_SIZE);
    this->label.setFillColor(sf::Color::White);
    this->label.setStyle(sf::Text::Regular);
    this->label.setString(initLabel);
    textW = this->label.getLocalBounds().width;
    textH = this->label.getLocalBounds().height;

    if (lLeft) {
        this->label.setOrigin(textW, textH / 2);
        this->label.setPosition(this->xPos - 12, this->yPos + 6);
    } else {
        this->label.setOrigin(0, textH / 2);
        this->label.setPosition(this->xPos + 24, this->yPos + 6);
    }

    for (int i = 0; i < 2; ++i) {
        this->sprites[i].setTexture(*GUI_COMMON_TEXTURE);
        this->sprites[i].setTextureRect(sf::IntRect(288 + i * 16, 0, 16, 16));
        this->sprites[i].setPosition(initX, initY);
    }
}

void GUI::Checkbox::updateAndDraw(sf::RenderWindow *inWindow) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*inWindow);

    if (mousePos.x > xPos && mousePos.y > yPos && mousePos.x < this->xPos + 16 && mousePos.y < this->yPos + 16) {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttonHeld) {

            if (this->checkState == CHECK_STATE::UNCHECKED) {
                this->checkState = CHECK_STATE::CHECKED;
            }
            else {
                this->checkState = CHECK_STATE::UNCHECKED;
            }
        }
        this->buttonHeld = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }

    inWindow->draw(this->sprites[(int)checkState]);
    inWindow->draw(this->label);
}
