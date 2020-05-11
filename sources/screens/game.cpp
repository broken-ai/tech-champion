#include "../../headers/screens/game.hpp"


GameScreen::GameScreen(const bool &isMultiPlayer=false) {
    this->currentSubScreen = GAME_SUBSCREEN::MENU;
    this->map = new Map();
    this->isMultiPlayer = isMultiPlayer;

    // In game menu elements
    const uint8_t buttonMargin = 5;
    this->resumeButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 200, "Resume");
    this->saveButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 232 + buttonMargin, "Save");
    this->settingsButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 264 + 2 * buttonMargin, "Settings");
    this->exitButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 296 + 3 * buttonMargin, "Exit");

    // Menu elements
    this->menuNewGameButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 200, "New game");
    this->menuLoadGameButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 232 + buttonMargin, "Load game");
    this->menuBackButton = new GUI::Button(g_config.WINDOW_WIDTH / 2 - 48, 264 + 2 * buttonMargin, "Back");

    /// FOR TESTING
    // Load test map
    if (!this->map->load(TESTMAP)) {
        openMessageBox("Can't load " + TESTMAP + " map.");
        exit(EXIT_FAILURE);
    }

    int tempX, tempY;

    for (int i = 0; i < this->map->layers[4].events.size(); i++) {
        for (int j = 0; j < this->map->layers[4].events[i].size(); j++) {
            if (this->map->layers[4].events[i][j].type == EVENT::SPAWN_POS) {
                tempX = j * 32 - 16;
                tempY = i * 32 - 32;
            }
        }
    }

    this->player = new Player(0, tempX, tempY);
    this->opponents.push_back(new Bot(1000, 0));

    for (Bot* opponent : this->opponents) {
        if (!opponent->loadSkin(BASE_FOLDER + "media/bot1.png")) {
            openMessageBox("Failed to load bot's skin");
            exit(EXIT_FAILURE);
        }
    }
    /// FOR TESTING

    if (!this->player->loadSkin(BASE_FOLDER + g_config.SKIN_FILENAME)) {
        openMessageBox("Failed to load skin");
        exit(EXIT_FAILURE);
    }

    this->statsTable = new StatsTable(this->opponents, this->player);
}

const SCREEN GameScreen::drawGame(sf::RenderWindow *window) {
    // Cheat console
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        if (this->cheatConsole.isOpen) {
            this->cheatConsole.isOpen = true;
        }
        else {
            this->cheatConsole.isOpen = false;
        }
    }*/
    this->player->update(this->map);
    this->map->drawBackground(window, this->player->cameraX, this->player->cameraY);

    for (size_t i = 0; i < g_rm.bullets.size(); i++) {
        g_rm.bullets[i]->update(this->map);
        g_rm.bullets[i]->draw(window);
    }
    this->player->draw(window);
    for (Bot* opponent : this->opponents) {
        opponent->updateState(this->map, this->player);
        opponent->update(this->map);
        opponent->draw(window);
    }

    this->map->drawForeground(window, this->player->cameraX, this->player->cameraY);
    window->setView(this->player->view);  // Set the view of the player

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

        // Set screenshot as background
        sf::Vector2u windowSize = window->getSize();
        sf::Texture *tempTexture = new sf::Texture();
        tempTexture->create(windowSize.x, windowSize.y);
        tempTexture->update(*window);
        this->menuBackground.setTexture(*tempTexture);
        this->menuBackground.setColor(sf::Color(127, 127, 127, 255));

        this->currentSubScreen = GAME_SUBSCREEN::IN_GAME_MENU;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {

        // Show the stats table
        this->statsTable->show(window);
    }
    return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
}

SCREEN GameScreen::run(sf::RenderWindow *window) {
    if (this->currentSubScreen == GAME_SUBSCREEN::GAME) {
        return this->drawGame(window);
    }
    else if (this->currentSubScreen == GAME_SUBSCREEN::IN_GAME_MENU) {
        return this->drawInGameMenu(window);
    }
    else if (this->currentSubScreen == GAME_SUBSCREEN::MENU) {
        /// FOR TESTING
        this->currentSubScreen = GAME_SUBSCREEN::GAME;
        // return this->drawMenu(window);
    }
    return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
}

const SCREEN GameScreen::drawInGameMenu(sf::RenderWindow *window) {
    window->setView(window->getDefaultView());
    window->draw(this->menuBackground);
    this->resumeButton->updateAndDraw(window);
    this->saveButton->updateAndDraw(window);
    this->settingsButton->updateAndDraw(window);
    this->exitButton->updateAndDraw(window);

    if (this->resumeButton->state == GUI::STATE::RELEASED) {
        this->resumeButton->state = GUI::STATE::NORMAL;
        this->currentSubScreen = GAME_SUBSCREEN::GAME;
        window->setView(this->player->view);
        return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
    }
    else if (this->exitButton->state == GUI::STATE::RELEASED) {
        this->exitButton->state = GUI::STATE::NORMAL;
        return SCREEN::MAIN_MENU;
    }
    else if (this->saveButton->state == GUI::STATE::RELEASED) {
        this->saveButton->state = GUI::STATE::NORMAL;
        cout << "Save button pressed" << endl;
    }
    else if (this->settingsButton->state == GUI::STATE::RELEASED) {
        this->settingsButton->state = GUI::STATE::NORMAL;
        cout << "Settings button pressed" << endl;
    }
    return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
}

const SCREEN GameScreen::drawMenu(sf::RenderWindow *window) {
    this->menuNewGameButton->updateAndDraw(window);
    this->menuLoadGameButton->updateAndDraw(window);
    this->menuBackButton->updateAndDraw(window);

    if (this->menuNewGameButton->state == GUI::STATE::RELEASED) {
        this->menuNewGameButton->state = GUI::STATE::NORMAL;
        this->currentSubScreen = GAME_SUBSCREEN::GAME;

        // Ask user to choose a map from the list of maps
        /// TODO

        return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
    }
    else if (this->menuLoadGameButton->state == GUI::STATE::RELEASED) {
        this->menuLoadGameButton->state = GUI::STATE::NORMAL;
        this->currentSubScreen = GAME_SUBSCREEN::GAME;
        return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
    }
    else if (this->menuBackButton->state == GUI::STATE::RELEASED) {
        this->menuBackButton->state = GUI::STATE::NORMAL;
        return SCREEN::MAIN_MENU;
    }
    return this->isMultiPlayer ? SCREEN::GAME_MULTIPLAYER : SCREEN::GAME_SINGLEPLAYER;
}

GameScreen::~GameScreen() {
    delete &this->player;
    delete &this->map;
    delete &this->resumeButton;
    delete &this->saveButton;
    delete &this->settingsButton;
    delete &this->exitButton;
    delete &this->statsTable;
}
