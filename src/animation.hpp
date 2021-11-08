#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include "base.hpp"

/*
Hierarchy:
 AnimSet is a collection of animations of the same subject (like different animations of an object or players). It manages the loading of its animations.
  Animation is a collection of sprites. It doesn't have its own loading function, instead it is managed by the AnimSet class.
   A sprite is a still image that can be drawn to the screen as is, or can be manipulated.

AnimPlayer handles playing an animation by getting frames from an instance of Animation class based on its counters and other variables.
This class is instanced by other classes that have graphics drawn to the screen.
*/

class Animation { // a container class for animation frames (sprites) and some data
public:
	sf::Texture texture;
	int frameCount; // number of frames the animation consists of
	int width;
	int height;

	Animation();
	~Animation();
};

class AnimSet { // a container class for AnimFrames instances
public:
	std::string name;
	std::vector<Animation> animations;

	AnimSet();																				 // creates an empty animation set
	AnimSet(std::string filepath, std::string name); // creates an instance of this class and tries to load the contents of an animation set file from the specified path
	~AnimSet();
};

class AnimPlayer { // a class for cycling through animation frames stored in instances of Animation
private:
    sf::Sprite sprite; // used to cycle through parts of the animation texture and display them
    int speed;		// in frames per second
	int curFrame;	// what frame is currently being displayed
	bool flipped; // true, if animation faces left, false otherwise
	sf::Clock counter;

public:
    AnimPlayer();
	~AnimPlayer();

	void reset();																			   // resets the animation to the first frame
	void play(const int& xPos, const int& yPos, const Animation& animation, const int8_t& directionH, const int8_t& directionV, const bool& draw, sf::RenderWindow* inWindow); // updates curFrame based on the speed of the animation
	//void setFlip(const int16_t& direction);													   // -1 for left, 1 for right
	void setSpeed(const unsigned int& speed);
	int getFrame();
	void setFrame(const unsigned int& frame);
};

#endif // _ANIMATION_HPP_
