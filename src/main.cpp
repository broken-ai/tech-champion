/**
TODO:

- Ask user to choose a map from the list of maps. (in GameScreen::drawMenu)
- Debug console (spawn objects, modify variables, etc.)
- Settings screen in the in-game menu.
- Game menu.
- Multi-player
- Background on the main menu.
- Spawn protection.
- Shooting.
- Weapons.
- Show game stats with tab.
- HUD.
- Show Broken AI logo on LoadingScreen.
- Show some nice graphics on LoadingScreen.
*/

#include "base.hpp"
#include "config.hpp"
#include "player.hpp"


int main(const int argc, const char** argv) {
    Config globalConfig;
    std::string gameBaseFolder = "";
    ResourceManager globalResourceManager;

    Utils::setBaseDir(gameBaseFolder, argv[0]);
    std::cout << "[INFO]: base folder: " + gameBaseFolder + "\n";
    PHYSFS_init(argv[0]);
    std::cout << "[INFO]: PhysFS initialized.\n";

    // Load global resources
    if (std::filesystem::exists(gameBaseFolder + "config.ini")) {
        std::cout << "[INFO]: Config file exists. Calling load function...\n";
        globalConfig.loadConfig(gameBaseFolder + "config.ini");
        std::cout << "[INFO]: Config file successfully loaded.\n";
    }
    /*if (!GAME_FONT->loadFromFile(BASE_FOLDER + "font/FreeSans.ttf")) {
        std::cout << "[ERROR]: Can't open game font.\n";
        return EXIT_FAILURE;
    }
    if (!GUI_COMMON_TEXTURE->loadFromFile(BASE_FOLDER + "media/gui.png")) {
        std::cout << "ERROR: Can't open GUI texture files.";
        return EXIT_FAILURE;
    }*/

    uint8_t menuItem = 0;

    // Window setup

    std::cout << "[INFO]: Creating game window...";
    sf::Event windowEvent;
    sf::RenderWindow window(sf::VideoMode(globalConfig.WINDOW_WIDTH, globalConfig.WINDOW_HEIGHT), WINDOW_TITLE, globalConfig.FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close);
    window.setFramerateLimit(globalConfig.FPS_LIMIT);
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    window.requestFocus();
    window.resetGLStates();
    std::cout << " done.\n";

    if (globalResourceManager.load(gameBaseFolder)) {
        std::cout << "[INFO]: Resources successfully loaded.\n";
    }

    Map testMap;
    std::cout << "[INFO]: Loading test map...\n";
    if (!testMap.load(gameBaseFolder + "\\content\\maps\\test.tcm", gameBaseFolder)) return 1;

    Player testPlayer(&globalConfig, 0, 128, 128);
    std::cout << "[INFO]: Player instance successfully created.\n";
    if (testPlayer.loadSkin(&globalResourceManager)) std::cout << "[INFO]: Player skin loaded.\n";
    else std::cout << "[ERROR]: Failed to load player skin.\n";

    GAMESTATE gameState = GAMESTATE::MAIN_MENU;

    // Main game loop
    while (window.isOpen()) {
        while (window.pollEvent(windowEvent)) {
            if (windowEvent.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Update and draw calls
		if (gameState == GAMESTATE::MAIN_MENU) {
            bool menuKeyHeld;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !menuKeyHeld) {
                if (menuItem > 0) menuItem--;
                else menuItem = 3;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !menuKeyHeld) {
                if (menuItem < 3) menuItem++;
                else menuItem = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !menuKeyHeld) {
                if (menuItem == 0) gameState = GAMESTATE::INGAME;
                else if (menuItem == 3) window.close();
            }

            for (int i = 0; i < 4; i++) {
                globalResourceManager.menuText.setString(menuStrings[i]);
                if (i != menuItem) globalResourceManager.menuText.setPosition(32, 360 + i * 32);
                else globalResourceManager.menuText.setPosition(64, 360 + i * 32);
                window.draw(globalResourceManager.menuText);
            }

            menuKeyHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		} else if (gameState == GAMESTATE::INGAME) {

			testPlayer.update(&globalConfig, &testMap);

			/*for (size_t i = 0; i < g_rm.bullets.size(); i++) {
                g_rm.bullets[i]->update(this->map);
                g_rm.bullets[i]->draw(window);
            }*/

            testMap.drawBackground(&window, testPlayer.cameraX, testPlayer.cameraY, &globalConfig);
            testPlayer.draw(&globalResourceManager, &window);
            testMap.drawForeground(&window, testPlayer.cameraX, testPlayer.cameraY, &globalConfig);

			window.setView(testPlayer.view); // Set the view of the player
		}

        window.display();
    }


    PHYSFS_deinit();
    return EXIT_SUCCESS;
}
