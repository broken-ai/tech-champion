#ifndef _SLIDER_HPP_
#define _SLIDER_HPP_

class Slider {
    /**
    Example usage:

    ```
    Slider slider(100, 100, gameFont);
	slider.create(20, 450);
	slider.setSliderValue(235);

	...
	slider.draw(window);
	...

    ```
    */
public:
	sf::RectangleShape slider;
	sf::RectangleShape axis;
	sf::Text text;
	int minValue;
	int maxValue;
	int xCord;
	int yCord;
	int axisWidth;
	int axisHeight;
	int sliderWidth;
	int sliderHeight;
	float sliderValue;

	Slider(const uint16_t &xPos, const uint16_t &yPos);
	~Slider();
	const sf::Text returnText(const uint16_t &x, const uint16_t &y, const std::string &z, const uint8_t &fontSize);
	const void create(const uint16_t &min, const uint16_t &max);
	const void setSliderValue(const float &newValue);
	const void setSliderPercentValue(const float &newPercentValue);
	void updateAndDraw(sf::RenderWindow *window);
};

#endif // _SLIDER_HPP_
