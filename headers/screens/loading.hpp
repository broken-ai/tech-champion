#ifndef _LOADING_HPP_
#define _LOADING_HPP_

class LoadingScreen : public Screen {
private:
    sf::Text loadingText;
    sf::Sprite logo;
    sf::Sprite sfmlLogo;

public:
    LoadingScreen();
    ~LoadingScreen();
    virtual SCREEN run(sf::RenderWindow *window);
};

#endif // _LOADING_HPP_
