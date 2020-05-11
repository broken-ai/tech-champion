#ifndef _SIMPLE_BUTTON_HPP_
#define _SIMPLE_BUTTON_HPP_

class SimpleButton {
    /**
    Simple button with a basic colored background
    */
public:
    uint16_t xPos;
    uint16_t yPos;
    uint16_t width;
    uint16_t height;
    STATE state;
    sf::Text label;
    sf::RectangleShape body;

    SimpleButton(const uint16_t &initX, const uint16_t &initY, const uint16_t &initW, const uint16_t &initH, const std::string &initLabel);
    void updateAndDraw(sf::RenderWindow *inWindow);
};

#endif // _SIMPLE_BUTTON_HPP_
