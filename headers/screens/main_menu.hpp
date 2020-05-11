#ifndef _MAIN_MENU_HPP_
#define _MAIN_MENU_HPP_

class MainMenuScreen : public Screen {
private:
    sf::Sprite logo;
    GUI::Button* singlePlayerButton;
    GUI::Button* multiPlayerButton;
    GUI::Button* settingsButton;
    GUI::Button* exitButton;

public:
    MainMenuScreen();
    ~MainMenuScreen();
    virtual SCREEN run(sf::RenderWindow *window);
};

#endif // _MAIN_MENU_HPP_
