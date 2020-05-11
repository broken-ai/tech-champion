#include "../../headers/gui/text_button.hpp"


GUI::TextButton::TextButton(const uint16_t &xPos, const uint16_t &yPos, const uint16_t &width, const uint16_t &height, const std::string &text) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->text = text;

    this->body.setSize(sf::Vector2f(width, height));
    this->body.setFillColor(sf::Color(0, 0, 0, 255));
    this->body.setOutlineColor(sf::Color(0, 50, 100, 255));
    this->body.setOutlineThickness(1);
    this->body.setPosition(xPos, yPos);

    this->label.setString(text);
    this->label.setFont(*GAME_FONT);
    this->label.setCharacterSize(g_config.CHARACTER_SIZE);
    this->label.setFillColor(sf::Color::White);
    this->label.setStyle(sf::Text::Regular);
    this->label.setOrigin((int) this->label.getLocalBounds().width / 2,
                          (int) this->label.getLocalBounds().height / 2);
    this->label.setPosition(width / 2 + xPos, height / 2 + yPos - 2);
}

void GUI::TextButton::updateAndDraw(sf::RenderWindow *window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    this->label.setOrigin((int) this->label.getLocalBounds().width / 2,
                          (int) this->label.getLocalBounds().height / 2);

    if (mousePos.x > this->xPos && mousePos.y > this->yPos && mousePos.x < this->xPos + this->width && mousePos.y < this->yPos + this->height) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->state = STATE::CLICKED;
        }
        else if (this->state == STATE::CLICKED) {
            this->state = STATE::RELEASED;
        }
        else {
            this->body.setFillColor(sf::Color(96, 96, 96, 255));
            this->state = STATE::HOVERED;
        }
    }
    else {
        this->body.setFillColor(sf::Color(0, 0, 0, 255));
        this->state = STATE::NORMAL;
    }

    window->draw(this->body);
    window->draw(this->label);
}
