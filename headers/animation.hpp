#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

class Animation {
public:
    std::vector<sf::Sprite> frames;
    sf::Clock counter;
    int frameCount; // number of frames the animation consists of
    int speed; // in frames per second
    int curFrame; // what frame is currently being displayed
    int width;
    int height;
    bool flipped; // true, if animation faces left, false otherwise

    Animation();
    ~Animation();
    void reset(); // resets the animation to the first frame
    void play(const int &xPos, const int &yPos, const bool &draw, sf::RenderWindow* inWindow); // updates curFrame based on the speed of the animation
    void setFlip(const int16_t &direction); // -1 for left, 1 for right
    void setSpeed(const unsigned int &speed);
    void setFrame(const unsigned int &frame);
};

#endif // _ANIMATION_HPP_
