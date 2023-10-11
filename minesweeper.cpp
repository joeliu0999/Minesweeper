//
// Created by User on 12/4/2022.
//
#include "minesweeper.h"

int launch()
{
    render();
    return 0;
}
void restart(){
    Toolbox& myToolbox=Toolbox::getInstance();
    delete myToolbox.gameState;
    myToolbox.gameState=new GameState();
}
void render(){
    Toolbox &myToolbox = Toolbox::getInstance();

    //split digits and push into a vector
    sf::Texture digitsTexture; digitsTexture.loadFromFile("images/digits.png");
    sf::Sprite digit_0Sprite(digitsTexture,sf::IntRect(0,0,21,32));
    sf::Sprite digit_1Sprite(digitsTexture,sf::IntRect(21,0,21,32));
    sf::Sprite digit_2Sprite(digitsTexture,sf::IntRect(42,0,21,32));
    sf::Sprite digit_3Sprite(digitsTexture,sf::IntRect(63,0,21,32));
    sf::Sprite digit_4Sprite(digitsTexture,sf::IntRect(84,0,21,32));
    sf::Sprite digit_5Sprite(digitsTexture,sf::IntRect(105,0,21,32));
    sf::Sprite digit_6Sprite(digitsTexture,sf::IntRect(126,0,21,32));
    sf::Sprite digit_7Sprite(digitsTexture,sf::IntRect(147,0,21,32));
    sf::Sprite digit_8Sprite(digitsTexture,sf::IntRect(168,0,21,32));
    sf::Sprite digit_9Sprite(digitsTexture,sf::IntRect(189,0,21,32));
    sf::Sprite digit_negativeSprite(digitsTexture,sf::IntRect(210,0,21,32));
    std::vector<sf::Sprite> digitCollection;
    digitCollection.push_back(digit_0Sprite);
    digitCollection.push_back(digit_1Sprite);
    digitCollection.push_back(digit_2Sprite);
    digitCollection.push_back(digit_3Sprite);
    digitCollection.push_back(digit_4Sprite);
    digitCollection.push_back(digit_5Sprite);
    digitCollection.push_back(digit_6Sprite);
    digitCollection.push_back(digit_7Sprite);
    digitCollection.push_back(digit_8Sprite);
    digitCollection.push_back(digit_9Sprite);
    digitCollection.push_back(digit_negativeSprite);


    sf::Texture debugTexture; debugTexture.loadFromFile("images/debug.png");
    sf::Texture face_happyTexture; face_happyTexture.loadFromFile("images/face_happy.png");
    sf::Texture face_winTexture; face_winTexture.loadFromFile("images/face_win.png");
    sf::Texture face_loseTexture; face_loseTexture.loadFromFile("images/face_lose.png");
    sf::Texture test_1Texture; test_1Texture.loadFromFile("images/test_1.png");
    sf::Texture test_2Texture; test_2Texture.loadFromFile("images/test_2.png");

    sf::Sprite debugSprite(debugTexture);
    sf::Sprite face_happySprite(face_happyTexture);
    sf::Sprite face_winSprite(face_winTexture);
    sf::Sprite face_loseSprite(face_loseTexture);
    sf::Sprite test_1Sprite(test_1Texture);
    sf::Sprite test_2Sprite(test_2Texture);

    sf::Texture tile_hiddenTexture; tile_hiddenTexture.loadFromFile("images/tile_hidden.png");
    sf::Sprite tile_hiddenSprite(tile_hiddenTexture);

    myToolbox.window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, <Yao Wen Liu>");
    while (myToolbox.window.isOpen())
    {
        //draw all the tile
        myToolbox.window.clear(sf::Color(255, 255, 255));
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                myToolbox.gameState->getTile(i,j)->draw();
            }
        }
        //setup button position
        if(myToolbox.gameState->getPlayStatus()==GameState::PLAYING) myToolbox.newGameButton->setSprite(&face_happySprite);
        myToolbox.newGameButton->getSprite()->setPosition(32 * 11.5, 32 * 16);
        myToolbox.window.draw(*(myToolbox.newGameButton->getSprite()));
        debugSprite.setPosition(32 * 15.5, 32 * 16);
        myToolbox.window.draw(debugSprite);
        test_1Sprite.setPosition(32 * 17.5, 32 * 16);
        myToolbox.window.draw(test_1Sprite);
        test_2Sprite.setPosition(32 * 19.5, 32 * 16);
        myToolbox.window.draw(test_2Sprite);

        //flag counter
        int flagDisplay=myToolbox.gameState->getMineCount()-myToolbox.gameState->getFlagCount();

        int zero=(flagDisplay-flagDisplay%100)/100;
        int first=((flagDisplay%100)-flagDisplay%10)/10;
        int second=flagDisplay%10;

        if(flagDisplay<0){
            digitCollection[10].setPosition(0,32*16);
            myToolbox.window.draw(digitCollection[10]);
            digitCollection[-first].setPosition(21,32*16);
            myToolbox.window.draw(digitCollection[-first]);
            digitCollection[-second].setPosition(42,32*16);
            myToolbox.window.draw(digitCollection[-second]);
        }
        else{
            digitCollection[zero].setPosition(0,32*16);
            myToolbox.window.draw(digitCollection[zero]);
            digitCollection[first].setPosition(21,32*16);
            myToolbox.window.draw(digitCollection[first]);
            digitCollection[second].setPosition(42,32*16);
            myToolbox.window.draw(digitCollection[second]);
        }


        myToolbox.window.display();

        sf::Event event;
        while (myToolbox.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) myToolbox.window.close();

            sf::Mouse myMouse;
            sf::Vector2i mousePosition;

            if(myToolbox.gameState->getPlayStatus()==GameState::PLAYING){
                //check if click on the designated area
                if(myMouse.isButtonPressed(sf::Mouse::Button::Left) or myMouse.isButtonPressed(sf::Mouse::Button::Right)){
                    if(myMouse.getPosition(myToolbox.window).y<32*16){
                        int x=-1, y=-1;
                        if (myMouse.isButtonPressed(sf::Mouse::Button::Left))
                        {
                            mousePosition = myMouse.getPosition(myToolbox.window);
                            for (int i = 1; i < 26; i++)
                            {
                                for (int j = 1; j < 17; j++)
                                {
                                    if ((mousePosition.x < i * 32) && (mousePosition.y < j * 32))
                                    {
                                        x = i-1;
                                        y = j-1;
                                        break;
                                    }
                                }
                                //prevent x from getting assigned to 24
                                if(x!=-1) break;
                            }
                            myToolbox.gameState->getTile(x, y)->onClickLeft();
                            myToolbox.gameState->getTile(x,y)->revealNeighbors();
                            if(checkWin()==true) myToolbox.gameState->setPlayStatus(GameState::WIN);
                        }
                        else if (myMouse.isButtonPressed(sf::Mouse::Button::Right))
                        {
                            mousePosition = myMouse.getPosition(myToolbox.window);
                            for (int i = 1; i < 26; i++)
                            {
                                for (int j = 1; j < 17; j++)
                                {
                                    if ((mousePosition.x < i * 32) && (mousePosition.y < j * 32))
                                    {
                                        x = i-1;
                                        y = j-1;
                                        break;
                                    }
                                }
                                //prevent x from getting assigned to 24
                                if(x!=-1) break;
                            }
                            myToolbox.gameState->getTile(x, y)->onClickRight();
                        }
                    }
                }
                //setup click area for buttons
                if(myMouse.isButtonPressed(sf::Mouse::Button::Left)){
                    mousePosition = myMouse.getPosition(myToolbox.window);
                    if(32*11.5<mousePosition.x && mousePosition.x<32*13.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.newGameButton->onClick();
                    }
                    if(32*15.5<mousePosition.x && mousePosition.x<32*17.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.debugButton->onClick();
                    }
                    if(32*17.5<mousePosition.x && mousePosition.x<32*19.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.testButton1->onClick();
                    }
                    if(32*19.5<mousePosition.x && mousePosition.x<32*21.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.testButton2->onClick();
                    }
                }

                if(myToolbox.gameState->getPlayStatus()==GameState::LOSS){
                    myToolbox.newGameButton->setSprite(&face_loseSprite);
                }
                else if(myToolbox.gameState->getPlayStatus()==GameState::WIN){
                    myToolbox.newGameButton->setSprite(&face_winSprite);
                }
            }
            //if lost, the only button that work will be reset
            else if(myToolbox.gameState->getPlayStatus()==GameState::LOSS){
                myToolbox.newGameButton->setSprite(&face_loseSprite);
                if(myMouse.isButtonPressed(sf::Mouse::Button::Left)){
                    mousePosition = myMouse.getPosition(myToolbox.window);
                    if(32*11.5<mousePosition.x && mousePosition.x<32*13.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.newGameButton->onClick();
                    }
                }
            }
            //you win, click face to restart
            else{
                myToolbox.newGameButton->setSprite(&face_winSprite);
                if(myMouse.isButtonPressed(sf::Mouse::Button::Left)){
                    mousePosition = myMouse.getPosition(myToolbox.window);
                    if(32*11.5<mousePosition.x && mousePosition.x<32*13.5 && 32*16<mousePosition.y && mousePosition.y <32*18){
                        myToolbox.newGameButton->onClick();
                    }
                }
            }


        }

    }
}
void toggleDebugMode(){
    Toolbox& myToolbox=Toolbox::getInstance();
    sf::Texture mineTexture; mineTexture.loadFromFile("images/mine.png");
    sf::Sprite mineSprite(mineTexture);
    if(getDebugMode()==false){
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                if(myToolbox.gameState->getTile(i,j)->getStateNum()==9) myToolbox.gameState->getTile(i,j)->setState(Tile::EXPLODED);
            }
        }
        myToolbox.gameState->setDebug(true);
    }
    else{
        for(int i=0;i<25;i++){
            for(int j=0;j<16;j++){
                if(myToolbox.gameState->getTile(i,j)->getStateNum()==9) myToolbox.gameState->getTile(i,j)->setState(Tile::HIDDEN);
            }
        }
        myToolbox.gameState->setDebug(false);
    }
}

bool getDebugMode(){
    Toolbox& myToolbox=Toolbox::getInstance();
    if(myToolbox.gameState->getDebug()) return true;
    else return false;
}
bool checkWin(){
    Toolbox& myToolbox=Toolbox::getInstance();
    for(int i=0;i<25;i++){
        for(int j=0;j<16;j++){
            if(myToolbox.gameState->getTile(i,j)->getState()==Tile::HIDDEN && myToolbox.gameState->getTile(i,j)->getStateNum()!=9) return false;
        }
    }
    return true;
}