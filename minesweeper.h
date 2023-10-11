//
// Created by User on 12/4/2022.
//

#ifndef PROJOECT4_MINESWEEPER_H
#define PROJOECT4_MINESWEEPER_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include "Tile.h"
#include "Toolbox.h"

int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();
bool checkWin();

#endif //PROJOECT4_MINESWEEPER_H
