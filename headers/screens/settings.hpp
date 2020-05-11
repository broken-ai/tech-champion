#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

class SettingsScreen : public Screen {
private:
    GUI::Button *toMainMenuButton;
    GUI::TextButton *upButton;
    GUI::TextButton *downButton;
    GUI::TextButton *leftButton;
    GUI::TextButton *rightButton;
    GUI::TextButton *jumpButton;
    GUI::TextButton *shootButton;
    GUI::TextButton *rollButton;
    GUI::TextButton *lockButton;
    sf::Text *screenTitle;
    sf::Text *settingsTitle;
    sf::Text *controlsTitle;
    sf::Text *upKeyLabel;
    sf::Text *downKeyLabel;
    sf::Text *leftKeyLabel;
    sf::Text *rightKeyLabel;
    sf::Text *jumpKeyLabel;
    sf::Text *shootKeyLabel;
    sf::Text *rollKeyLabel;
    sf::Text *lockKeyLabel;
    sf::Text *volumeTitle;
    sf::Text *masterVolumeLabel;
    sf::Text *soundVolumeLabel;
    sf::Text *musicVolumeLabel;
    GUI::Slider *masterVolumeSlider;
    GUI::Slider *soundVolumeSlider;
    GUI::Slider *musicVolumeSlider;
    GUI::Checkbox *fullscreenCheckbox;
    bool waitingForKey;

    const sf::Keyboard::Key getPressedKey(sf::Keyboard::Key currentKey);
public:
    SettingsScreen();
    ~SettingsScreen();
    virtual SCREEN run(sf::RenderWindow *window);
};

#endif // _SETTINGS_HPP_
