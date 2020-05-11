/**
TODO:

- Ask user to choose a map from the list of maps. (in GameScreen::drawMenu)
- Cheat console.
- Settings screen in the in-game menu.
- Game menu.
- Multi player
- Background on the main menu.
- Spawn protection.
- Shooting.
- Guns.
- Show game stats with tab.
- HUD.
- Show broken-ai logo on LoadingScreen.
- Show some nice graphics on LoadingScreen.
*/
#include "base.cpp"
#include "config.cpp"
#include "physfs_stream.cpp"
#include "gui/gui.cpp"
#include "popup.cpp"
#include "map/map.cpp"
#include "object/bullet.cpp"
#include "resource_manager.cpp"
#include "animation.cpp"
#include "anim_set.cpp"
#include "entity/entity.cpp"
#include "stats_table.cpp"
#include "screens/screen.cpp"


int main(const int argc, const char** argv) {

    // Setups
    srand(time(NULL));
    Utils::setBaseDir(argv[0]);
    PHYSFS_init(argv[0]);


    // Load global variables
    if (Utils::isFileExists(BASE_FOLDER + "config.ini")) {
        g_config.loadConfig(BASE_FOLDER + "config.ini");
    }
    if (!GAME_FONT->loadFromFile(BASE_FOLDER + "font/FreeSans.ttf")) {
        cout << "ERROR: Can't open font files." << endl;
        return EXIT_FAILURE;
    }
    if (!GUI_COMMON_TEXTURE->loadFromFile(BASE_FOLDER + "media/gui.png")) {
        openMessageBox("ERROR: Can't open texture files.");
        return EXIT_FAILURE;
    }


    // Window setup
    sf::Event windowEvent;
    sf::RenderWindow window(sf::VideoMode(g_config.WINDOW_WIDTH, g_config.WINDOW_HEIGHT), WINDOW_TITLE, g_config.FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close);
    window.setFramerateLimit(g_config.FPS_LIMIT);
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    window.requestFocus();
    window.resetGLStates();


    // Indices need to match with the corresponding SCREEN enum value
    Screen* screens[5];
    screens[0] = new LoadingScreen();
    SCREEN currentScreenIndex = SCREEN::LOADING;
    SCREEN nextScreenIndex = SCREEN::LOADING;

    std::vector<uint16_t> spawnPositionsX;
    std::vector<uint16_t> spawnPositionsY;

    // Main game loop
    while (window.isOpen()) {
        while (window.pollEvent(windowEvent)) {
            if (windowEvent.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.clear();
        nextScreenIndex = screens[(int) currentScreenIndex]->run(&window);


        // Free the memory of the not used screens,
        // and only store the current screen.
        if (currentScreenIndex != nextScreenIndex) {
            delete[] screens[(int) currentScreenIndex];

            if (nextScreenIndex == SCREEN::LOADING) {
                screens[(int) nextScreenIndex] = new LoadingScreen();
                window.setView(window.getDefaultView());
            }
            else if (nextScreenIndex == SCREEN::MAIN_MENU) {
                screens[(int) nextScreenIndex] = new MainMenuScreen();
                window.setView(window.getDefaultView());
            }
            else if (nextScreenIndex == SCREEN::SETTINGS) {
                screens[(int) nextScreenIndex] = new SettingsScreen();
                window.setView(window.getDefaultView());
            }
            else if (nextScreenIndex == SCREEN::GAME_SINGLEPLAYER) {
                screens[(int) nextScreenIndex] = new GameScreen(false);
            }
            else if (nextScreenIndex == SCREEN::GAME_MULTIPLAYER) {
                screens[(int) nextScreenIndex] = new GameScreen(true);
            }
            currentScreenIndex = nextScreenIndex;
        }

        g_rm.update();
        window.display();
    }


    PHYSFS_deinit();
    return EXIT_SUCCESS;
}
