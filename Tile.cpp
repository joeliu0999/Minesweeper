//
// Created by User on 12/4/2022.
//
#include "Tile.h"

Tile::Tile(sf::Vector2f position){
    tilePosition=position;
    theState=State::HIDDEN;
}
sf::Vector2f Tile::getLocation(){
    return tilePosition;
}
Tile::State Tile::getState(){
    return theState;
}
std::array<Tile*, 8>& Tile::getNeighbors(){
    return myArray;
}
void Tile::setState(Tile::State _state){
    theState=_state;
}
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors){
    myArray=_neighbors;
}
void Tile::onClickLeft(){
    if(theState==State::HIDDEN){
        if(stateNum==9) theState=State::EXPLODED;
        else theState=State::REVEALED;
    }
}
void Tile::onClickRight(){
    if(theState==State::HIDDEN) theState=State::FLAGGED;
    else if(theState==State::FLAGGED) theState=State::HIDDEN;
}
//draw tile with respect to state and stateNum
void Tile::draw(){
    Toolbox& myToolbox=Toolbox::getInstance();
    sf::Texture tile_revealedTexture; tile_revealedTexture.loadFromFile("images/tile_revealed.png");
    sf::Sprite tile_revealedSprite(tile_revealedTexture);
    tile_revealedSprite.setPosition(tilePosition);

    if(theState==State::HIDDEN){
        sf::Texture tile_hiddenTexture; tile_hiddenTexture.loadFromFile("images/tile_hidden.png");
        sf::Sprite tile_hiddenSprite(tile_hiddenTexture);
        tile_hiddenSprite.setPosition(tilePosition);
        myToolbox.window.draw(tile_hiddenSprite);
    }

    else if(theState==State::FLAGGED){
        sf::Texture tile_hiddenTexture; tile_hiddenTexture.loadFromFile("images/tile_hidden.png");
        sf::Sprite tile_hiddenSprite(tile_hiddenTexture);
        tile_hiddenSprite.setPosition(tilePosition);
        myToolbox.window.draw(tile_hiddenSprite);
        sf::Texture flagTexture; flagTexture.loadFromFile("images/flag.png");
        sf::Sprite flagSprite(flagTexture);
        flagSprite.setPosition(tilePosition);
        myToolbox.window.draw(flagSprite);
    }
    else if(theState==State::EXPLODED){
        sf::Texture tile_revealedTexture; tile_revealedTexture.loadFromFile("images/tile_revealed.png");
        sf::Sprite tile_revealedSprite(tile_revealedTexture);
        tile_revealedSprite.setPosition(tilePosition);
        myToolbox.window.draw(tile_revealedSprite);
        sf::Texture mineTexture; mineTexture.loadFromFile("images/mine.png");
        sf::Sprite mineSprite(mineTexture);
        mineSprite.setPosition(tilePosition);
        myToolbox.window.draw(mineSprite);

        if(getDebugMode()==false) myToolbox.gameState->setPlayStatus(GameState::LOSS);
    }
    else{ //State::REVEALED
        if(stateNum==0){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
        }
        else if(stateNum==1){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_1Texture; number_1Texture.loadFromFile("images/number_1.png");
            sf::Sprite number_1Sprite(number_1Texture);
            number_1Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_1Sprite);
        }
        else if(stateNum==2){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_2Texture; number_2Texture.loadFromFile("images/number_2.png");
            sf::Sprite number_2Sprite(number_2Texture);
            number_2Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_2Sprite);
        }
        else if(stateNum==3){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_3Texture; number_3Texture.loadFromFile("images/number_3.png");
            sf::Sprite number_3Sprite(number_3Texture);
            number_3Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_3Sprite);
        }
        else if(stateNum==4){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_4Texture; number_4Texture.loadFromFile("images/number_4.png");
            sf::Sprite number_4Sprite(number_4Texture);
            number_4Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_4Sprite);
        }
        else if(stateNum==5){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_5Texture; number_5Texture.loadFromFile("images/number_5.png");
            sf::Sprite number_5Sprite(number_5Texture);
            number_5Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_5Sprite);
        }
        else if(stateNum==6){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_6Texture; number_6Texture.loadFromFile("images/number_6.png");
            sf::Sprite number_6Sprite(number_6Texture);
            number_6Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_6Sprite);
        }
        else if(stateNum==7){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_7Texture; number_7Texture.loadFromFile("images/number_7.png");
            sf::Sprite number_7Sprite(number_7Texture);
            number_7Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_7Sprite);
        }
        else if(stateNum==8){
            tile_revealedSprite.setPosition(tilePosition);
            myToolbox.window.draw(tile_revealedSprite);
            sf::Texture number_8Texture; number_8Texture.loadFromFile("images/number_8.png");
            sf::Sprite number_8Sprite(number_8Texture);
            number_8Sprite.setPosition(tilePosition);
            myToolbox.window.draw(number_8Sprite);
        }
    }
}

void Tile::revealNeighbors(){
    if(stateNum==0){
        for(int i=0;i<8;i++){
            if(myArray[i]!=nullptr){
                if(myArray[i]->getState()!=REVEALED)
                {
                    myArray[i]->setState(REVEALED);
                    if (myArray[i]->getStateNum() == 0) myArray[i]->revealNeighbors();
                }
            }
        }
    }
}

int Tile::getStateNum(){
    return stateNum;
}
void Tile::setStateNum(int num){
    stateNum=num;
}