#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include <physfs.h>

#ifdef _WIN32
// Windows OS
#include <windows.h>

#else
// Linux or Mac OS
#include <sys/types.h>
#include <dirent.h>

#endif // _WIN32

using std::cout;
using std::endl;

enum class SCREEN {
    LOADING,
    MAIN_MENU,
    SETTINGS,
    GAME_SINGLEPLAYER,
    GAME_MULTIPLAYER
};

enum class DIRECTION {
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    LEFT_UP,
    RIGHT_UP,
    LEFT_DOWN,
    RIGHT_DOWN
};


/**

Global constants

*/
std::string BASE_FOLDER = "";

#define M_PI 3.14159265358979323846
#define INF std::numeric_limits<float>::infinity()

#define TILESET_FOLDER "tilesets/"
#define MUSIC_FOLDER "media/music/"
#define MAP_FOLDER "maps/"
#define BULLET_FOLDER "media/bullets/"
#define ANIMATION_FOLDER "media/animations/"

#define WINDOW_TITLE "Tech Champion"
#define STARTING_HEALTH 100
#define GRAVITY_CONST .375
#define BASIC_SPAWN_TIME_SECONDS 2
#define BASIC_BULLET_SPEED 10

#define TESTMAP BASE_FOLDER + MAP_FOLDER + "test.tcm"

sf::Font *GAME_FONT = new sf::Font();
sf::Texture *GUI_COMMON_TEXTURE = new sf::Texture();


/**

Keyboard

*/
#define KEY_COUNT 101
const std::string KEY_LABELS[KEY_COUNT] = {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Escape",
    "Left Control",
    "Left Shift",
    "Left Alt",
    "Left System",
    "Right Control",
    "Right Shift",
    "Right Alt",
    "Right System",
    "Menu",
    "Left Bracket",
    "Right Bracket",
    "Semicolon",
    "Comma",
    "Period",
    "Quote",
    "Slash",
    "Backslash",
    "Tilde",
    "Equal",
    "Hyphen",
    "Space",
    "Enter",
    "Backspace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Left arrow",
    "Right arrow",
    "Up arrow",
    "Down arrow",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "Pause"
};


namespace Utils {

    const std::vector<std::string> listdir(const std::string &dirName) {
        std::vector<std::string> fileNames;
#ifdef _WIN32
        std::string pattern(dirName);
        pattern.append("\\*");
        WIN32_FIND_DATA data;
        HANDLE hFind;
        if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
            do {
                fileNames.push_back(data.cFileName);
            } while (FindNextFile(hFind, &data) != 0);
            FindClose(hFind);
        }
#else
        DIR* dirp = opendir(dirName.c_str());
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            fileNames.push_back(dp->d_name);
        }
        closedir(dirp);
#endif // _WIN32
        return fileNames;
    }

    /**
    @returns true if the given file exists
    */
    const bool isFileExists(const std::string &fileName) {
        // std::ifstream infile(fileName);
        // return infile.good();
        struct stat buffer;
        return (stat(fileName.c_str(), &buffer) == 0);
    }

    /**
    Parses the current working directory from the exeFilePath parameter.
    */
    const void setBaseDir(const std::string &exeFilePath) {
        uint8_t lastSlashIndex = 0;

        for (uint8_t i = 0; i < exeFilePath.length(); i++) {
            if (exeFilePath[i] == '\\' || exeFilePath[i] == '/') {
                lastSlashIndex = i;
            }
        }

        BASE_FOLDER = exeFilePath.substr(0, lastSlashIndex + 1);
    }

    template<typename T> std::string to_string(const T &n) {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }

}


// Header files
/*#include "../headers/animation.hpp"
#include "../headers/config.hpp"
#include "../headers/physfs_stream.hpp"
#include "../headers/map/tileset.hpp"
#include "../headers/map/map.hpp"
#include "../headers/entity/entity.hpp"
#include "../headers/stats_table.hpp"
#include "../headers/gui/gui.hpp"
#include "../headers/object/bullet.hpp"
#include "../headers/screens/screen.hpp"
#include "../headers/resource_manager.hpp"*/
