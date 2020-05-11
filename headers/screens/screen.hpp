#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

class Screen {
    /**
    * @summary Represents abstract screen.
    */
public:

    /**
    * Draws the screen on the given window.
    * @returns The next [enum class SCREEN] to be shown
    */
    virtual SCREEN run(sf::RenderWindow *window) = 0;
};

#endif // _SCREEN_HPP_
