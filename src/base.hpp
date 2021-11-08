#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "physfs_stream.hpp"

enum class GAMESTATE {
	LOADING,
	MAIN_MENU,
	SETTINGS,
	INGAME
};

#define M_PI 3.14159265358979323846
#define INF std::numeric_limits<float>::infinity()

#define TILESET_FOLDER "content/tilesets/"
#define MUSIC_FOLDER "content/music/"
#define MAP_FOLDER "content/maps/"
#define ANIMATION_FOLDER "content/animations/"

#define WINDOW_TITLE "Tech Champion [Early Alpha]"
#define STARTING_HEALTH 100 // should be moved, due to planned perk system (increased HP perk?)
#define GRAVITY_CONST .375	// should move this to a variable, so low-gravity scenarios can be made via scripting
#define BASIC_SPAWN_TIME_SECONDS 2

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
	"Plus",
	"Minus",
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

const std::string menuStrings[4] = {
    "Training mode",
    "Multi-player mode",
    "Settings",
    "Quit"
};

namespace Utils {
bool doesFileExist(std::string fileName);
void setBaseDir(std::string& toSet, std::string exeFilePath);
template <typename T>
std::string to_string(const T& n);
}

#endif // _BASE_HPP_
