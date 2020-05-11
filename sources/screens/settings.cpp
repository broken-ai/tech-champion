#include "../../headers/screens/settings.hpp"


SettingsScreen::SettingsScreen() {
    this->toMainMenuButton = new GUI::Button(32, g_config.WINDOW_HEIGHT - 48, "Back");
    this->waitingForKey = false;

    // Key buttons
    int commonX = g_config.WINDOW_WIDTH / 2;
    int commonWidth = 11 * g_config.CHARACTER_SIZE;
    uint8_t commonHeight = 1.5 * g_config.CHARACTER_SIZE;
    uint8_t buttonMargin = 10;
    uint8_t titleSize = 1.5 * g_config.CHARACTER_SIZE;

    this->upButton = new GUI::TextButton(commonX, 4 * g_config.CHARACTER_SIZE + buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.UP]);
    this->downButton = new GUI::TextButton(commonX, 5 * g_config.CHARACTER_SIZE + 2 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.DOWN]);
    this->leftButton = new GUI::TextButton(commonX, 6 * g_config.CHARACTER_SIZE + 3 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.LEFT]);
    this->rightButton = new GUI::TextButton(commonX, 7 * g_config.CHARACTER_SIZE + 4 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.RIGHT]);
    this->jumpButton = new GUI::TextButton(commonX, 8 * g_config.CHARACTER_SIZE + 5 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.JUMP]);
    this->shootButton = new GUI::TextButton(commonX, 9 * g_config.CHARACTER_SIZE + 6 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.SHOOT]);
    this->rollButton = new GUI::TextButton(commonX, 10 * g_config.CHARACTER_SIZE + 7 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.ROLL]);
    this->lockButton = new GUI::TextButton(commonX, 11 * g_config.CHARACTER_SIZE + 8 * buttonMargin, commonWidth, commonHeight, KEY_LABELS[g_config.AIM_LOCK]);

    // Keyboard labels
    this->settingsTitle = new sf::Text("Settings", *GAME_FONT, 2 * g_config.CHARACTER_SIZE);
    this->controlsTitle = new sf::Text("Controls", *GAME_FONT, titleSize);
    this->upKeyLabel = new sf::Text("Up", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->downKeyLabel = new sf::Text("Down", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->leftKeyLabel = new sf::Text("Left", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->rightKeyLabel = new sf::Text("Right", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->jumpKeyLabel = new sf::Text("Jump", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->shootKeyLabel = new sf::Text("Shoot", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->rollKeyLabel = new sf::Text("Roll", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->lockKeyLabel = new sf::Text("Aim lock", *GAME_FONT, g_config.CHARACTER_SIZE + 1);

    this->volumeTitle = new sf::Text("Volume", *GAME_FONT, titleSize);
    this->masterVolumeLabel = new sf::Text("Master", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->soundVolumeLabel = new sf::Text("Sound", *GAME_FONT, g_config.CHARACTER_SIZE + 1);
    this->musicVolumeLabel = new sf::Text("Music", *GAME_FONT, g_config.CHARACTER_SIZE + 1);

    // Set position of keyboard labels
    this->settingsTitle->setPosition(10, 0);
    this->settingsTitle->setStyle(sf::Text::Bold);
    this->controlsTitle->setPosition(commonX, 13);
    this->controlsTitle->setStyle(sf::Text::Bold);
    this->upKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->upButton->yPos);
    this->downKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->downButton->yPos);
    this->leftKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->leftButton->yPos);
    this->rightKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->rightButton->yPos);
    this->jumpKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->jumpButton->yPos);
    this->shootKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->shootButton->yPos);
    this->rollKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->rollButton->yPos);
    this->lockKeyLabel->setPosition(commonX - 9 * g_config.CHARACTER_SIZE, this->lockButton->yPos);

    // Sliders
    this->volumeTitle->setPosition(commonX, 15 * g_config.CHARACTER_SIZE + 8 * buttonMargin);
    this->volumeTitle->setStyle(sf::Text::Bold);

    this->masterVolumeSlider = new GUI::Slider(g_config.WINDOW_WIDTH / 2, 18 * g_config.CHARACTER_SIZE + 10 * buttonMargin);
    this->masterVolumeLabel->setPosition(commonX - 12 * g_config.CHARACTER_SIZE, 18 * g_config.CHARACTER_SIZE + 10 * buttonMargin - 10);
    this->masterVolumeSlider->create(0, 100);
    this->masterVolumeSlider->setSliderValue(g_config.MASTER_VOLUME);

    this->soundVolumeSlider = new GUI::Slider(g_config.WINDOW_WIDTH / 2, 22 * g_config.CHARACTER_SIZE + 10 * buttonMargin);
    this->soundVolumeLabel->setPosition(commonX - 12 * g_config.CHARACTER_SIZE, 22 * g_config.CHARACTER_SIZE + 10 * buttonMargin - 10);
    this->soundVolumeSlider->create(0, 100);
    this->soundVolumeSlider->setSliderValue(g_config.SOUND_VOLUME);

    this->musicVolumeSlider = new GUI::Slider(g_config.WINDOW_WIDTH / 2, 26 * g_config.CHARACTER_SIZE + 10 * buttonMargin);
    this->musicVolumeLabel->setPosition(commonX - 12 * g_config.CHARACTER_SIZE, 26 * g_config.CHARACTER_SIZE + 10 * buttonMargin - 10);
    this->musicVolumeSlider->create(0, 100);
    this->musicVolumeSlider->setSliderValue(g_config.MUSIC_VOLUME);

    // Screen settings
    this->screenTitle = new sf::Text("Screen", *GAME_FONT, titleSize);
    this->screenTitle->setPosition(commonX, 28 * g_config.CHARACTER_SIZE + 11 * buttonMargin + 1);
    this->screenTitle->setStyle(sf::Text::Bold);

    this->fullscreenCheckbox = new GUI::Checkbox(this->musicVolumeSlider->xCord + this->musicVolumeSlider->axisWidth - 16,
                                                 29 * g_config.CHARACTER_SIZE + 11 * buttonMargin + 16, "Full screen", true);
    this->fullscreenCheckbox->checkState = g_config.FULLSCREEN ? GUI::CHECK_STATE::CHECKED : GUI::CHECK_STATE::UNCHECKED;
}

SCREEN SettingsScreen::run(sf::RenderWindow *window) {
    this->toMainMenuButton->updateAndDraw(window);

    // Volume sliders
    window->draw(*this->screenTitle);
    window->draw(*this->volumeTitle);
    window->draw(*this->masterVolumeLabel);
    window->draw(*this->soundVolumeLabel);
    window->draw(*this->musicVolumeLabel);
    window->draw(*this->settingsTitle);
    this->masterVolumeSlider->updateAndDraw(window);
    this->soundVolumeSlider->updateAndDraw(window);
    this->musicVolumeSlider->updateAndDraw(window);
    this->fullscreenCheckbox->updateAndDraw(window);

    // Keyboard buttons
    window->draw(*this->controlsTitle);
    this->upButton->updateAndDraw(window);
    this->downButton->updateAndDraw(window);
    this->leftButton->updateAndDraw(window);
    this->rightButton->updateAndDraw(window);
    this->jumpButton->updateAndDraw(window);
    this->shootButton->updateAndDraw(window);
    this->rollButton->updateAndDraw(window);
    this->lockButton->updateAndDraw(window);
    window->draw(*this->upKeyLabel);
    window->draw(*this->downKeyLabel);
    window->draw(*this->leftKeyLabel);
    window->draw(*this->rightKeyLabel);
    window->draw(*this->jumpKeyLabel);
    window->draw(*this->shootKeyLabel);
    window->draw(*this->rollKeyLabel);
    window->draw(*this->lockKeyLabel);

    // Handle buttons
    if (this->toMainMenuButton->state == GUI::STATE::RELEASED) {
        g_config.save(BASE_FOLDER + "config.ini");
        return SCREEN::MAIN_MENU;
    }
    else if (this->upButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->upButton->label.setString("Please press a key ...");
        this->upButton->updateAndDraw(window);
        window->display();
        g_config.UP = this->getPressedKey(g_config.UP);
        this->upButton->label.setString(KEY_LABELS[g_config.UP]);
    }
    else if (this->downButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->downButton->label.setString("Please press a key ...");
        this->downButton->updateAndDraw(window);
        window->display();
        g_config.DOWN = this->getPressedKey(g_config.DOWN);
        this->downButton->label.setString(KEY_LABELS[g_config.DOWN]);
    }
    else if (this->leftButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->leftButton->label.setString("Please press a key ...");
        this->leftButton->updateAndDraw(window);
        window->display();
        g_config.LEFT = this->getPressedKey(g_config.LEFT);
        this->leftButton->label.setString(KEY_LABELS[g_config.LEFT]);
    }
    else if (this->rightButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->rightButton->label.setString("Please press a key ...");
        this->rightButton->updateAndDraw(window);
        window->display();
        g_config.RIGHT = this->getPressedKey(g_config.RIGHT);
        this->rightButton->label.setString(KEY_LABELS[g_config.RIGHT]);
    }
    else if (this->jumpButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->jumpButton->label.setString("Please press a key ...");
        this->jumpButton->updateAndDraw(window);
        window->display();
        g_config.JUMP = this->getPressedKey(g_config.JUMP);
        this->jumpButton->label.setString(KEY_LABELS[g_config.JUMP]);
    }
    else if (this->shootButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->shootButton->label.setString("Please press a key ...");
        this->shootButton->updateAndDraw(window);
        window->display();
        g_config.SHOOT = this->getPressedKey(g_config.SHOOT);
        this->shootButton->label.setString(KEY_LABELS[g_config.SHOOT]);
    }
    else if (this->rollButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->rollButton->label.setString("Please press a key ...");
        this->rollButton->updateAndDraw(window);
        window->display();
        g_config.ROLL = this->getPressedKey(g_config.ROLL);
        this->rollButton->label.setString(KEY_LABELS[g_config.ROLL]);
    }
    else if (this->lockButton->state == GUI::STATE::RELEASED && !this->waitingForKey) {
        this->waitingForKey = true;
        this->lockButton->label.setString("Please press a key ...");
        this->lockButton->updateAndDraw(window);
        window->display();
        g_config.AIM_LOCK = this->getPressedKey(g_config.AIM_LOCK);
        this->lockButton->label.setString(KEY_LABELS[g_config.AIM_LOCK]);
    }

    g_config.MASTER_VOLUME = this->masterVolumeSlider->sliderValue;
    g_config.SOUND_VOLUME = this->soundVolumeSlider->sliderValue;
    g_config.MUSIC_VOLUME = this->musicVolumeSlider->sliderValue;
    g_config.FULLSCREEN = fullscreenCheckbox->checkState == GUI::CHECK_STATE::CHECKED;
    return SCREEN::SETTINGS;
}

const sf::Keyboard::Key SettingsScreen::getPressedKey(sf::Keyboard::Key currentKey) {
    while (this->waitingForKey) {
        for (int i = 0; i < KEY_COUNT; i++) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                this->waitingForKey = false;
                return currentKey;
            }
            else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) i)) {
                this->waitingForKey = false;
                return (sf::Keyboard::Key) i;
            }
        }
    }

    this->waitingForKey = false;
    return currentKey;
}

SettingsScreen::~SettingsScreen() {
    delete &this->toMainMenuButton;
    delete &this->upButton;
    delete &this->downButton;
    delete &this->leftButton;
    delete &this->rightButton;
    delete &this->jumpButton;
    delete &this->shootButton;
    delete &this->rollButton;
    delete &this->lockButton;
    delete &this->upKeyLabel;
    delete &this->downKeyLabel;
    delete &this->leftKeyLabel;
    delete &this->rightKeyLabel;
    delete &this->jumpKeyLabel;
    delete &this->shootKeyLabel;
    delete &this->rollKeyLabel;
    delete &this->lockKeyLabel;
    delete &this->controlsTitle;
    delete &this->settingsTitle;
    delete &this->masterVolumeLabel;
    delete &this->masterVolumeSlider;
    delete &this->soundVolumeLabel;
    delete &this->soundVolumeSlider;
    delete &this->musicVolumeLabel;
    delete &this->musicVolumeSlider;
    delete &this->fullscreenCheckbox;
    delete &this->screenTitle;
}
