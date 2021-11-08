#include "map.hpp"


Map::Map() {}

void Map::drawBackground(sf::RenderWindow* inWindow, const int &inCamX, const int &inCamY, Config* inConfig) {
    int startX;
    int startY;
    int endX;
    int endY;

    int layerOffsetX;
    int layerOffsetY;

    sf::Sprite currentSprite;

    for (int layerIndex = 0; layerIndex < 5; layerIndex++) {
        layerOffsetX = inCamX * (this->layers[layerIndex].xSpeed - 1);
        layerOffsetY = inCamY * (this->layers[layerIndex].ySpeed - 1);

        startX = (int)((inCamX + layerOffsetX) / 32 - 1); //these now cut the layer drawing off where they should, but might need some debugging, we'll see
        if (startX < 0) startX = 0;
        startY = (int)((inCamY + layerOffsetY) / 32 - 1);
        if (startY < 0) startY = 0;

        endX = (int)((inCamX + inConfig->WINDOW_WIDTH + layerOffsetX) / 32);
        if (endX > this->layers[layerIndex].width - 1) endX = this->layers[layerIndex].width - 1;
        endY = (int)((inCamY + inConfig->WINDOW_HEIGHT + layerOffsetY) / 32);
        if (endY > this->layers[layerIndex].height - 1) endY = this->layers[layerIndex].height - 1;

        for (int i = startY; i <= endY; i++) {
            for (int j = startX; j <= endX; j++) {
                if (this->layers[layerIndex].tiles[i][j] != 0) {
                    currentSprite = this->tileset.tileSprites[this->layers[layerIndex].tiles[i][j]];
                    currentSprite.setPosition((j * 32) - layerOffsetX, (i * 32) - layerOffsetY);
                    inWindow->draw(currentSprite);
                }
            }
        }
    }
}

void Map::drawForeground(sf::RenderWindow* inWindow, const int &inCamX, const int &inCamY, Config* inConfig) {
    int startX;
    int startY;
    int endX;
    int endY;

    int layerOffsetX;
    int layerOffsetY;

    sf::Sprite currentSprite;

    for (int layerIndex = 5; layerIndex < 8; layerIndex++) {
        layerOffsetX = inCamX * (this->layers[layerIndex].xSpeed - 1);
        layerOffsetY = inCamY * (this->layers[layerIndex].ySpeed - 1);

        startX = (int)((inCamX + layerOffsetX) / 32 - 1);
        if (startX < 0) startX = 0;
        startY = (int)((inCamY + layerOffsetY) / 32 - 1);
        if (startY < 0) startY = 0;

        endX = (int)((inCamX + inConfig->WINDOW_WIDTH + layerOffsetX) / 32);
        if (endX > this->layers[layerIndex].width - 1) endX = this->layers[layerIndex].width - 1;
        endY = (int)((inCamY + inConfig->WINDOW_HEIGHT + layerOffsetY) / 32);
        if (endY > this->layers[layerIndex].height - 1) endY = this->layers[layerIndex].height - 1;

        for (int i = startY; i <= endY; i++) {
            for (int j = startX; j <= endX; j++) {
                if (this->layers[layerIndex].tiles[i][j] != 0) {
                    currentSprite = this->tileset.tileSprites[this->layers[layerIndex].tiles[i][j]];
                    currentSprite.setPosition((j * 32) - layerOffsetX, (i * 32) - layerOffsetY);
                    inWindow->draw(currentSprite);
                }
            }
        }
    }
}

std::vector<uint16_t> Map::parseTileRow(const std::string &line) {
    std::vector<uint16_t> row;
    std::string currentNum = "";

    for (unsigned int i = 0; i < line.length(); i++) {
        if (line[i] == ' ' || line[i] == '\t') {
            continue;
        }

        if (line[i] == ',') {
            //std::cout << "[parseTileRow1] currentNum: " + currentNum + "\n";
            row.push_back(uint16_t(std::stoi(currentNum)));
            currentNum = "";
            continue;
        }

        currentNum += line[i];
    }

    // Save the last one too
    //std::cout << "[parseTileRow2] currentNum: " + currentNum + "\n";
    //row.push_back(uint16_t(std::stoi(currentNum))); // this refuses to work for some reason
    row.push_back(0);
    return row;
}

bool Map::setLayerProperty(Layer *layer, const std::string &key, const std::string &value) {
    if (key.empty() || value.empty()) {  // Check them first
        return false;
    }

    if (key == "width") {
        layer->width = std::strtol(value.c_str(), NULL, 0);
    }
    else if (key == "height") {
        layer->height = std::strtol(value.c_str(), NULL, 0);
    }
    else if (key == "xSpeed") {
        layer->xSpeed = std::stof(value.c_str(), NULL);
    }
    else if (key == "ySpeed") {
        layer->ySpeed = std::stof(value.c_str(), NULL);
    }
    else if (key == "xSpeedAuto") {
        layer->xSpeedAuto = std::stof(value.c_str(), NULL);
    }
    else if (key == "ySpeedAuto") {
        layer->ySpeedAuto = std::stof(value.c_str(), NULL);
    }
    else if (key == "xOffset") {
        layer->xOffset = std::strtol(value.c_str(), NULL, 0);
    }
    else if (key == "yOffset") {
        layer->yOffset = std::strtol(value.c_str(), NULL, 0);
    }
    return true;
}

bool Map::load(std::string fileName, const std::string &inPath) {
    if (!/*Utils::doesFileExist*/std::filesystem::exists(fileName)) {
        std::cout << "[ERROR]: Map file does not exist. (" + fileName + ")\n";
        return false;
    }

    std::cout << "[INFO]: Map file seems to exist. Trying to load now.\n";

    std::string currentLine;
    bool inALayer = false;
    bool inATile = false;
    bool inKey = false;
    bool isTileSetLoaded = false;
    bool loadInProgress = true;
    unsigned int layerIndex = 0;
    unsigned int keyValueLinePos = 0;
    unsigned int pos = 0;
    unsigned int prevLineIndex = 0;
    unsigned int lineIndex = 0;
    std::string keyStr = "";
    std::string valueStr = "";
    std::vector<std::vector<uint16_t>> currentTiles;
    std::ifstream mapFile;

    // Wait for opening the file
    mapFile.open(fileName);
    while (!mapFile.is_open()) {}

    // Go line by line
    while (std::getline(mapFile, currentLine) && loadInProgress) {

        // Load in global properties too
        if (!isTileSetLoaded && currentLine.substr(0, 12) == "tileset_file") {
            std::string value;
            bool inValue = false;
            bool inString = false;

            for (unsigned int i = 0; i < currentLine.length(); i++) {
                if (currentLine[i] == ' ' && !inString) continue;

                if (currentLine[i] == '=') {
                    inValue = true;
                    continue;
                }

                if (inValue) {
                    if (currentLine[i] == '"') {
                        inString = true;
                        continue;
                    }
                    else if (inString && currentLine[i] == '"') {
                        inString = false;
                        break;
                    }

                    if (inString) {
                        value += currentLine[i];
                    }
                }
            }

            if (!this->tileset.initialize(inPath + "\\content\\tilesets\\" + value)) return false;
            isTileSetLoaded = true;
        }


        // Go char by char
        for (pos = 0; pos < currentLine.length(); pos++) {

            // Ignore comment
            if (currentLine[pos] == '#') {
                break;
            }
            else if(currentLine[pos] == ' ' || currentLine[pos] == '\t') {
                continue;
            }

            if (currentLine[pos] == '{') {
                inALayer = true;
                continue;
            }
            else if (currentLine[pos] == '}') {
                inALayer = false;

                // Save this layer
                this->layers[layerIndex].tiles = currentTiles;
                currentTiles.clear();

                layerIndex++;
                if (layerIndex > 7) {
                    loadInProgress = false;
                    break;
                }
                continue;
            }

            if (inALayer) {

                // Handle tiles
                if (currentLine[pos] == '[') {
                    inATile = true;
                    continue;
                }
                else if (currentLine[pos] == ']') {
                    inATile = false;
                    continue;
                }

                if (inATile && lineIndex != prevLineIndex) {
                    prevLineIndex = lineIndex;
                    currentTiles.push_back(this->parseTileRow(currentLine));
                }

                // Handle properties
                if (currentLine[pos] == '=') {
                    inKey = true;
                    keyStr = "";
                    valueStr = "";

                    // Parse value and key
                    // Go char by char (again)
                    for (keyValueLinePos = 0; keyValueLinePos < currentLine.length(); keyValueLinePos++) {
                        if (currentLine[keyValueLinePos] == ' ' || currentLine[keyValueLinePos] == '\t') continue;

                        if (currentLine[keyValueLinePos] == '=') {
                            inKey = false;
                            continue;
                        }

                        if (inKey) {
                            keyStr.append(std::string(1, currentLine[keyValueLinePos]));
                        }
                        else {
                            valueStr.append(std::string(1, currentLine[keyValueLinePos]));
                        }
                    }

                    this->setLayerProperty(&this->layers[layerIndex], keyStr, valueStr);
                    //pos = keyValueLinePos;  ///0xC0000005
                    continue;
                }

            }

        }

        lineIndex++;
    }
    mapFile.close();

    // Read in the event layer too
    mapFile.open(fileName);
    while (!mapFile.is_open()) {}

    std::vector<Event> eventRow;
    Event currentEvent(EVENT::NONE, 0);
    std::string eventString = "";
    std::string paramString = "";
    uint8_t pCounter = 0;
    bool inEvent = false;
    bool inEventValue = false;
    loadInProgress = true;
    this->layers[4].events = {};

    while (std::getline(mapFile, currentLine) && loadInProgress) {
        for (pos = 0; pos < currentLine.length(); pos++) {

            // Ignore comment and whitespace
            if (currentLine[pos] == '#') {
                break;
            }
            else if(currentLine[pos] == ' ' || currentLine[pos] == '\t') {
                continue;
            }

            if (currentLine[pos] == '{') {
                pCounter++;
                continue;
            }

            if (pCounter == 9) {
                if (currentLine[pos] == '}') {
                    loadInProgress = false;
                    break;
                }

                if (currentLine[pos] == '[') {
                    inEvent = true;
                    inEventValue = true;
                    continue;
                }
                else if (currentLine[pos] == ']') {
                    inEvent = false;
                    inEventValue = true;

                    currentEvent.type = (EVENT) std::atoi(eventString.c_str());
                    currentEvent.parameter = std::atoi(paramString.c_str());

                    eventRow.push_back(currentEvent);

                    currentEvent.type = EVENT::NONE;
                    currentEvent.parameter = 0;

                    eventString = "";
                    paramString = "";
                    continue;
                }

                if (inEvent) {
                    if (currentLine[pos] == ',') {
                        inEventValue = !inEventValue;
                        continue;
                    }

                    if (inEventValue) {
                        eventString += currentLine[pos];
                    }
                    else {
                        paramString += currentLine[pos];
                    }

                }

            }
        }

        if (pCounter == 9 && eventRow.size() > 0) {
            this->layers[4].events.push_back(eventRow);
            eventRow = {};
        }
    }

    mapFile.close();

    std::cout << "[INFO]: Map loaded successfully.\n";
    return true;
}

Map::~Map() {
    delete[] &this->layers[0];
    delete[] &this->layers[1];
    delete[] &this->layers[2];
    delete[] &this->layers[3];
    delete[] &this->layers[4];
    delete[] &this->layers[5];
    delete[] &this->layers[6];
    delete[] &this->layers[7];
    delete &this->tileset;
    delete &this->name;
}


int getTile(Map* inMap, const uint8_t &layer, const int &xTile, const int &yTile) {
    if (xTile >= 0 && xTile < inMap->layers[layer].width && yTile >= 0 && yTile < inMap->layers[layer].height) return inMap->layers[layer].tiles[yTile][xTile];
    return 0;
}

bool maskedPixel(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos) {
    if (xPos >= 0 && xPos < inMap->layers[layer].width * 32 && yPos >= 0 && yPos < inMap->layers[layer].height * 32) {
        uint16_t tileAtCoords = getTile(inMap, layer, xPos / 32, yPos / 32);
        uint8_t xTile = tileAtCoords % 10;
        uint16_t yTile = (unsigned int)(tileAtCoords / 10);
        return inMap->tileset.mask[yTile * 32 + yPos % 32][xTile * 32 + xPos % 32];
    }
    return true;
}

bool maskedHLine(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos, const int &length) {
    if (length >= 0) {
        for (int i = xPos; i < xPos + length; i++) {
            if (maskedPixel(inMap, layer, i, yPos)) return true;
        }
    } else {
        for (int i = xPos - length; i > xPos; i--) {
            if (maskedPixel(inMap, layer, i, yPos)) return true;
        }
    }
    return false;
}

int maskedFirstHArea(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos, const int hLength, const int &vLength) {
    if (hLength >= 0) {
        for (int i = 0; i < hLength; i++) {
            if (maskedVLine(inMap, layer, xPos + i, yPos, vLength)) return i;
        }
    } else {
        for (int i = 0; i > hLength; i--) {
            if (maskedVLine(inMap, layer, xPos + i, yPos, vLength)) return i;
        }
    }
    return hLength;
}

bool maskedVLine(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos, const int &length) {
    if (length >= 0) {
        for (int i = yPos; i < yPos + length; i++) {
            if (maskedPixel(inMap, layer, xPos, i)) return true;
        }
    } else {
        for (int i = yPos - length; i > yPos; i--) {
            if (maskedPixel(inMap, layer, xPos, i)) return true;
        }
    }
    return false;
}

int maskedTopVLine(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos, const int length) {
    for (int i = 0; i < length; i++) {
        if (maskedPixel(inMap, layer, xPos, yPos + i)) return i;
    }
    return length;
}

int maskedTopVArea(Map* inMap, const uint8_t &layer, const int &xPos, const int &yPos, const int &hLength, const int vLength) {
    if (vLength >= 0) {
        for (int i = 0; i < vLength; i++) {
            if (maskedHLine(inMap, layer, xPos, yPos + i, hLength)) return i;
        }
    } else {
        for (int i = 0; i > vLength; i--) {
            if (maskedHLine(inMap, layer, xPos, yPos + i, hLength)) return i;
        }
    }
    return vLength;
}
