//
// Created by User on 12/4/2022.
//

#ifndef PROJOECT4_TILE_H
#define PROJOECT4_TILE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "Toolbox.h"


class Tile{
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
    void revealNeighbors();
    int getStateNum();
    void setStateNum(int num);
private:
    sf::Vector2f tilePosition;
    State theState;
    std::array<Tile*, 8> myArray;
    int stateNum;
};

#endif //PROJOECT4_TILE_H
