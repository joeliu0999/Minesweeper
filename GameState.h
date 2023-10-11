//
// Created by User on 12/4/2022.
//

#ifndef PROJOECT4_GAMESTATE_H
#define PROJOECT4_GAMESTATE_H
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <fstream>

class Tile;
#include "Tile.h"
#include "Toolbox.h"

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile *getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
    bool getDebug();
    void setDebug(bool);
private:
    sf::Vector2i dimensions;
    int numberOfMines;
    int flagCount;
    std::vector<std::vector<Tile*>> myVector;
    std::vector<std::vector<int>> mineVector;
    PlayStatus stats=PLAYING;
    bool debug=false;
};

#endif //PROJOECT4_GAMESTATE_H
