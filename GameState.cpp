//
// Created by User on 12/4/2022.
//
#include "GameState.h"
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines){
    dimensions=_dimensions;
    numberOfMines=_numberOfMines;

    //set tile position
    for(int i=0;i<dimensions.x;i++){
        std::vector<Tile*> row;
        for(int j=0;j<dimensions.y;j++){
            sf::Vector2f pos(i*32,j*32);
            Tile* theTile=new Tile(pos);
            row.push_back(theTile);

        }
        myVector.push_back(row);
    }
    //set neighbor
    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            std::array<Tile*,8> neighbor;
            for(int k=0;k<8;k++) neighbor[k]=nullptr;
            if(i-1>-1&&j-1>-1) neighbor[0]=myVector[i-1][j-1];
            if(j-1>-1) neighbor[1]=myVector[i][j-1];
            if(i+1 < dimensions.x &&j-1>-1) neighbor[2]=myVector[i+1][j-1];
            if(i-1>-1) neighbor[3]=myVector[i-1][j];
            if(i+1<dimensions.x) neighbor[4]=myVector[i+1][j];
            if(i-1>-1&&j+1<dimensions.y) neighbor[5]=myVector[i-1][j+1];
            if(j+1<dimensions.y) neighbor[6]=myVector[i][j+1];
            if(i+1<dimensions.x && j+1<dimensions.y) neighbor[7]=myVector[i+1][j+1];
            myVector[i][j]->setNeighbors(neighbor);
        }

    }

    //set random mines
    std::vector<std::vector<int>> vec(dimensions.x,std::vector<int>(dimensions.y,0));
    mineVector=vec;

    srand(time(NULL));
    while(_numberOfMines!=0){
        int xRand=rand()%25;
        int yRand=rand()%16;
        if(mineVector[xRand][yRand]!=1){
            mineVector[xRand][yRand]=1;
            _numberOfMines--;
        }
    }
    //map mines on to the mineVector
    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            if(mineVector[i][j]==1) myVector[i][j]->setStateNum(9);
        }
    }

    //set stateNum(0-8: respective tile representation, 9: mine)
    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            int count=0;
            if(myVector[i][j]->getStateNum()!=9){
                for(int k=0;k<8;k++){
                    if(myVector[i][j]->getNeighbors()[k]!=nullptr){
                        if(myVector[i][j]->getNeighbors()[k]->getStateNum()==9) count++;
                    }
                }
                myVector[i][j]->setStateNum(count);
            }
        }
    }

}
GameState::GameState(const char *filepath)
{
    dimensions=sf::Vector2i(25,16);
    numberOfMines=50;

    //set tile position
    for(int i=0;i<dimensions.x;i++){
        std::vector<Tile*> row;
        for(int j=0;j<dimensions.y;j++){
            sf::Vector2f pos(i*32,j*32);
            Tile* theTile=new Tile(pos);
            row.push_back(theTile);

        }
        myVector.push_back(row);
    }

    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            std::array<Tile*,8> neighbor;
            for(int k=0;k<8;k++) neighbor[k]=nullptr;
            if(i-1>-1&&j-1>-1) neighbor[0]=myVector[i-1][j-1];
            if(j-1>-1) neighbor[1]=myVector[i][j-1];
            if(i+1 < dimensions.x &&j-1>-1) neighbor[2]=myVector[i+1][j-1];
            if(i-1>-1) neighbor[3]=myVector[i-1][j];
            if(i+1<dimensions.x) neighbor[4]=myVector[i+1][j];
            if(i-1>-1&&j+1<dimensions.y) neighbor[5]=myVector[i-1][j+1];
            if(j+1<dimensions.y) neighbor[6]=myVector[i][j+1];
            if(i+1<dimensions.x&&j+1<dimensions.y) neighbor[7]=myVector[i+1][j+1];
            myVector[i][j]->setNeighbors(neighbor);
        }

    }

    std::vector<std::vector<int>> vec(dimensions.x,std::vector<int>(dimensions.y,0));
    mineVector=vec;

    char* test= new char;
    int counter = 0;
    std::ifstream testFile(filepath);
    //read in all 400 digits, counter does not go up if white space is read
    while(counter < 400)
    {
        testFile.read(test, 1);
        if (*test == '1')
        {
            mineVector[counter % 25][counter/25]=1;
            counter++;

        }
        if (*test == '0'){
            mineVector[counter % 25][counter/25]=0;
            counter++;
        }

    }

    //stateNum9 is mine
    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            if(mineVector[i][j]==1) myVector[i][j]->setStateNum(9);
        }
    }

    for(int i=0;i<dimensions.x;i++){
        for(int j=0;j<dimensions.y;j++){
            int count=0;
            if(myVector[i][j]->getStateNum()!=9){
                for(int k=0;k<8;k++){
                    if(myVector[i][j]->getNeighbors()[k]!=nullptr){
                        if(myVector[i][j]->getNeighbors()[k]->getStateNum()==9) count++;
                    }
                }
                myVector[i][j]->setStateNum(count);
            }
        }
    }
}
int GameState::getFlagCount(){
    int flagCount=0;
    for(int i=0;i<dimensions.x;i++){
        for (int j=0;j<dimensions.y;j++){
            if(myVector[i][j]->getState()==Tile::FLAGGED) flagCount++;
        }
    }
    return flagCount;
}
int GameState::getMineCount(){
    numberOfMines=0;
    for(int i=0;i<25;i++){
        for(int j=0;j<16;j++){
            if(myVector[i][j]->getStateNum()==9) numberOfMines++;
        }
    }
    return numberOfMines;
}
Tile* GameState::getTile(int x, int y){
    return myVector[x][y];
}
GameState::PlayStatus GameState::getPlayStatus(){
    return stats;
}
void GameState::setPlayStatus(PlayStatus _status){
    stats=_status;
}
bool GameState::getDebug(){return debug;}
void GameState::setDebug(bool set){debug=set;}

