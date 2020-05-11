#ifndef _TEXT_BUTTON_HPP_
#define _TEXT_BUTTON_HPP_

class TextButton {
    /**
    Text what works like a button
    */
public:
    uint16_t xPos;
    uint16_t yPos;
    uint16_t width;
    uint16_t height;
    std::string text;
    sf::Text label;
    sf::RectangleShape body;
    STATE state;

    TextButton(const uint16_t &xPos, const uint16_t &yPos, const uint16_t &width, const uint16_t &height, const std::string &text);
    void updateAndDraw(sf::RenderWindow *window);
};

#endif // _TEXT_BUTTON_HPP_
