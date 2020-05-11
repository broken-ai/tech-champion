#ifndef _MAP_HPP_
#define _MAP_HPP_

enum class EVENT {
    NONE, //What it says on the tin.
    SPAWN_POS, //Starting position for the player. If more than one are placed on the level, the player will spawn at one of them randomly.
    TELEPORT, //If the player touches this event, they will be teleported to the location of a teleport destination with the corresponding ID.
    TELEPORT_DEST, //The destination of a teleport event. Use the same ID as a teleport event to link them together.
    ONE_WAY, //Placing this on a solid tile will make it possible to jump through it from underneath.
    SPRING, //Making contact with a spring will give the player a boost upwards.
    ELEVATOR, //Walking onto an elevator will activate it and take the player up to a given height.
    PITFALL, //Touching this event will instantly kill the player.
    INTERACT, //Special event with the intention of supporting custom scripted interactions (eg.: text sign)
    MAIN_AMMO, //Ammunition pickup for the player's selected main weapon.
    SUB_AMMO, //Ammunition pickup for the player's selected sub weapon.
    HEALTH_5, //Small health pickup. Gives 5 health points.
    HEALTH_25, //Medium health pickup. Gives 25 health points.
    HEALTH_50, //Large health pickup. Gives 50 health points.
    SHIELD_5, //Small shield pickup. Gives 5 shield points.
    SHIELD_25, //Medium shield pickup. Gives 25 shield points.
    SHIELD_50 //Large shield pickup. Gives 50 shield points.
};

class Event {
public:
    EVENT type;
    uint16_t parameter;

    Event(EVENT initType, uint16_t initParam) {
        this->type = initType;
        this->parameter = initParam;
    }
};

typedef struct Layer {
    std::vector<std::vector<uint16_t> > tiles;
    std::vector<std::vector<Event> > events; //only the fifth layer makes use of this matrix
    uint16_t width; // Layer width in tiles
    uint16_t height; // Layer height in tiles
    float xSpeed; // How much the layer moves horizontally compared to camera (1 is normal scrolling state, fixed for layer 4)
    float ySpeed; // How much the layer moves vertically compared to camera (1 is normal scrolling state, fixed for layer 4)
    float xSpeedAuto; // How much the layer moves horizontally independent of camera movement
    float ySpeedAuto; // How much the layer moves vertically independent of camera movement
    int16_t xOffset; // How much the layer is initially offset horizontally
    int16_t yOffset; // How much the layer is initially offset vertically
    bool loopX; //Whether the layer wraps around on the X axis (useful together with xSpeedAuto)
    bool loopY; //Whether the layer wraps around on the Y axis (useful together with ySpeedAuto)

    float xPos; // Horizontal scrolling state of the layer
    float yPos; // Vertical scrolling state of the layer
} Layer;


class Map {
/**
Example use:

```
Map *_map_ = new Map();
if (!_map_->load(BASE_FOLDER + MAP_FOLDER + "test.map")) {
    debug("Can't load test map.");
    return EXIT_FAILURE;
}
delete _map_;
```
*/
public:
    std::string name; // Name of the map to be displayed in menus and in-game
    Tileset tileset;
    Layer layers[8]; // The layers the map consists of

    Map(); // Should be initialized instead of using a load function
    ~Map();
    bool load(const std::string &filepath);

    /**
        Updates and draws a piece of layers 0-4 based on camera position and layer position
    */
    void drawBackground(sf::RenderWindow* inWindow, const int &inCamX, const int &inCamY);

    /**
        Updates and draws a piece of layers 5-7 based on camera position and layer position
    */
    void drawForeground(sf::RenderWindow* inWindow, const int &inCamX, const int &inCamY);

private:
    /**
        @returns One tile row from the given line
    */
    std::vector<uint16_t> parseTileRow(const std::string &line);

    /**
        Changes the input layer and sets it's given key to the given value
    */
    bool setLayerProperty(Layer *layer, const std::string &key, const std::string &value);
};


/**
    @returns the tileID of the tile at xTile and yTile
*/
int getTile(Map* inMap, const uint8_t layer, const int xTile, const int yTile);

/**
    @returns true if a pixel in inMap is masked in layer at (xPos, yPos)
*/
bool maskedPixel(Map* inMap, const uint8_t layer, const int xPos, const int yPos);

/**
    @returns true if any pixel in inMap is masked in layer from (xPos, yPos) to (xPos + length, yPos)
*/
bool maskedHLine(Map* inMap, const uint8_t layer, const int xPos, const int yPos, const int length);

/**
    @returns the index of the first vertical line it finds a masked pixel in
*/
int maskedFirstHArea(Map* inMap, const uint8_t layer, const int xPos, const int yPos, const int hLength, const int vLength);

/**
    @returns true if any pixel in inMap is masked in layer from (xPos, yPos) to (xPos, yPos + length)
*/
bool maskedVLine(Map* inMap, const uint8_t layer, const int xPos, const int yPos, const int length);

/**
    @returns the index of the topmost masked pixel in inMap in layer from (xPos, yPos) to (xPos, yPos + length)
*/
int maskedTopVLine(Map* inMap, const uint8_t layer, const int xPos, const int yPos, const int length);

/**
    @returns the index of the topmost horizontal line it finds a masked pixel in
*/
int maskedTopVArea(Map* inMap, const uint8_t layer, const int xPos, const int yPos, const int hLength, const int vLength);

#endif  // _MAP_HPP_
