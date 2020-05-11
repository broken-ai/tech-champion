#include "../../headers/screens/loading.hpp"


LoadingScreen::LoadingScreen() {
    this->loadingText = sf::Text("...", *GAME_FONT, g_config.CHARACTER_SIZE);
    this->loadingText.setPosition((int) (g_config.WINDOW_WIDTH / 2), g_config.WINDOW_HEIGHT - 50);

    sf::Image logoImage;
    logoImage.loadFromFile(BASE_FOLDER + "media/logo.png");
    sf::Texture *logoTexture = new sf::Texture();
    logoTexture->loadFromImage(logoImage);
    this->logo.setTexture(*logoTexture);
    this->logo.setPosition((int) (g_config.WINDOW_WIDTH / 2) - logoTexture->getSize().x / 2,
                           (int) (g_config.WINDOW_HEIGHT / 2) - logoTexture->getSize().y / 2);

    sf::Image sfmlLogoImage;
    sfmlLogoImage.loadFromFile(BASE_FOLDER + "media/sfml_logo.png");
    sf::Texture *sfmlLogoTexture = new sf::Texture();
    sfmlLogoTexture->loadFromImage(sfmlLogoImage);
    this->sfmlLogo.setTexture(*sfmlLogoTexture);
    this->sfmlLogo.setScale(0.15, 0.15);
    this->sfmlLogo.setPosition(25, g_config.WINDOW_HEIGHT - 75);
}

SCREEN LoadingScreen::run(sf::RenderWindow *window) {
    window->draw(this->logo);
    window->draw(this->loadingText);
    window->draw(this->sfmlLogo);
    window->display();

    // Loading resource manager
    g_rm.load();

    return SCREEN::MAIN_MENU;
}

LoadingScreen::~LoadingScreen() {
    delete &this->loadingText;
}
