#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
private:
    char userInput;     
    bool hasExited;     
    bool hasLost;       
    bool hasWon;       
    int currentScore;   

    int boardWidth;     
    int boardHeight;    

public:
    GameMechs();
    GameMechs(int width, int height);
    ~GameMechs(); // Destructor

    bool hasExitedGame() const;   
    void setExitGame();           

    bool hasLostGame() const;     
    void setLoseGame();           

    bool hasWonGame() const;      
    void setWinGame();            

    char getUserInput() const;    
    void setUserInput(char input); 
    void resetUserInput();        

    int getBoardWidth() const;    
    int getBoardHeight() const;   

    int getCurrentScore() const;  
    void updateScore(int currentLength); 
};

#endif