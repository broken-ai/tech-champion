#ifndef _CHECK_BOX_HPP_
#define _CHECK_BOX_HPP_

class Checkbox : public GUIElement {
    /**
    Clickable checkbox with 2 states: checked, unchecked
    */
public:
    sf::Text label;
    sf::Sprite sprites[2];
    bool buttonHeld;
    CHECK_STATE checkState;

    Checkbox(const uint16_t &initX, const uint16_t &initY, const std::string &initLabel, const bool &lLeft);
    void updateAndDraw(sf::RenderWindow *inWindow);
};

#endif // _CHECK_BOX_HPP_
