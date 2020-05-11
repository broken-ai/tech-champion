#ifndef _GUI_HPP_
#define _GUI_HPP_

enum class STATE {
    NORMAL,
    HOVERED,
    CLICKED,
    RELEASED
};

enum class CHECK_STATE {
    UNCHECKED,
    CHECKED
};


class GUIElement {
    /**
    Represents abstract GUI element.
    */

public:
    uint16_t xPos;
    uint16_t yPos;
    STATE state;

    /**
    Draws the GUI element on the given window.
    */
    virtual void updateAndDraw(sf::RenderWindow *inWindow) = 0;
};

#endif // _GUI_HPP_
