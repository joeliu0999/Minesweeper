//
// Created by User on 12/4/2022.
//

#include "Toolbox.h"

Toolbox& Toolbox::getInstance(){
    static Toolbox toolbox;
    return toolbox;
}

Toolbox::Toolbox() {
    gameState=new GameState();
    sf::Vector2f deBug(32*15.5,32*16);
    sf::Vector2f newGame(32 * 11.5, 32 * 16);
    sf::Vector2f test1(32*17.5,32*16);
    sf::Vector2f test2(32*19.5,32*16);
    debugButton=new Button(deBug,toggleDebugMode);
    newGameButton=new Button(newGame,restart);
    testButton1=new Button(test1,[this](){delete gameState; gameState=new GameState("boards/testboard1.brd");});
    testButton2=new Button(test2,[this](){delete gameState; gameState=new GameState("boards/testboard2.brd");});

}