#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

class Button : public GUIElement {
    /**
    Clickable button with 3 states: normal, hovered, pressed
    */
public:
    sf::Text label;
    sf::Sprite sprites[3];

    Button(const uint16_t &initX, const uint16_t &initY, const std::string &initLabel);
    void updateAndDraw(sf::RenderWindow* inWindow);
};

#endif // _BUTTON_HPP_

