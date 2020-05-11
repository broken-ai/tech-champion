#include "../../headers/screens/main_menu.hpp"


MainMenuScreen::MainMenuScreen() {
    sf::Image logoImage;
    logoImage.loadFromFile(BASE_FOLDER + "media/logo.png");
    sf::Texture *logoTexture = new sf::Texture();
    logoTexture->loadFromImage(logoImage);
    this->logo.setTexture(*logoTexture);
    this->logo.setPosition(g_config.WINDOW_WIDTH / 2 - logoTexture->getSize().x / 2, 136);

    uint8_t buttonMargin = 5;
    this->singlePlayerButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 200 + 10, "Single player");
    this->multiPlayerButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 232 + buttonMargin + 10, "Multi player");
    this->settingsButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 264 + 2*buttonMargin + 10, "Settings");
    this->exitButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 296 + 3*buttonMargin + 10, "Exit");
}

SCREEN MainMenuScreen::run(sf::RenderWindow *window) {
    window->draw(this->logo);
    this->singlePlayerButton->updateAndDraw(window);
    this->multiPlayerButton->updateAndDraw(window);
    this->settingsButton->updateAndDraw(window);
    this->exitButton->updateAndDraw(window);

    if (this->singlePlayerButton->state == GUI::STATE::RELEASED) {
        this->singlePlayerButton->state = GUI::STATE::NORMAL;
        return SCREEN::GAME_SINGLEPLAYER;
    }
    else if (this->multiPlayerButton->state == GUI::STATE::RELEASED) {
        this->multiPlayerButton->state = GUI::STATE::NORMAL;
        return SCREEN::GAME_MULTIPLAYER;
    }
    else if (this->settingsButton->state == GUI::STATE::RELEASED) {
        this->settingsButton->state = GUI::STATE::NORMAL;
        return SCREEN::SETTINGS;
    }
    else if (this->exitButton->state == GUI::STATE::RELEASED) {
        window->close();
        return SCREEN::LOADING;
    }

    return SCREEN::MAIN_MENU;
}

MainMenuScreen::~MainMenuScreen() {
    delete &this->singlePlayerButton;
    delete &this->multiPlayerButton;
    delete &this->settingsButton;
    delete &this->exitButton;
}
