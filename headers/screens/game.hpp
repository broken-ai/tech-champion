#ifndef _GAME_SCREEN_HPP_
#define _GAME_SCREEN_HPP_

enum class GAME_SUBSCREEN {
    MENU,
    GAME,
    IN_GAME_MENU
};


class GameScreen : public Screen {
private:
    Player *player;
    std::vector<Bot*> opponents;
    StatsTable *statsTable;
    Map *map;
    GAME_SUBSCREEN currentSubScreen;
    bool isMultiPlayer;

    // In game menu elements
    sf::Sprite menuBackground;
    GUI::Button *resumeButton;
    GUI::Button *saveButton;
    GUI::Button *settingsButton;
    GUI::Button *exitButton;

    // Menu buttons
    GUI::Button *menuNewGameButton;
    GUI::Button *menuLoadGameButton;
    GUI::Button *menuBackButton;

    const SCREEN drawInGameMenu(sf::RenderWindow *window);
    const SCREEN drawMenu(sf::RenderWindow *window);
    const SCREEN drawGame(sf::RenderWindow *window);

public:
    GameScreen(const bool &isMultiPlayer);
    ~GameScreen();
    virtual SCREEN run(sf::RenderWindow *window);
};

#endif // _GAME_SCREEN_HPP_
