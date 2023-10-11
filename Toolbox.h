//
// Created by User on 12/4/2022.
//

#ifndef PROJOECT4_TOOLBOX_H
#define PROJOECT4_TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include "minesweeper.h"
#include "Tile.h"
class Button;
class GameState;

class Toolbox{
public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    static Toolbox& getInstance();
private:
    Toolbox();
};

#endif //PROJOECT4_TOOLBOX_H
