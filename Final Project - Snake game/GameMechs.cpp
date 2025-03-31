#include <iostream>
#include "GameMechs.h"

GameMechs::GameMechs()
{
    userInput = 0;
    hasExited = false;
    hasLost = false;
    hasWon = false; // Initialize win flag
    currentScore = 0;

    boardWidth = 30;
    boardHeight = 15;
}

GameMechs::GameMechs(int width, int height)
{
    userInput = 0;
    hasExited = false;
    hasLost = false;
    hasWon = false; // Initialize win flag
    currentScore = 0;

    boardWidth = width;
    boardHeight = height;
}

GameMechs::~GameMechs()
{
    // No dynamic memory to free
}

bool GameMechs::hasExitedGame() const
{
    return hasExited;
}

void GameMechs::setExitGame()
{
    hasExited = true;
}

bool GameMechs::hasLostGame() const
{
    return hasLost;
}

void GameMechs::setLoseGame()
{
    hasLost = true;
}

bool GameMechs::hasWonGame() const
{
    return hasWon;
}

void GameMechs::setWinGame()
{
    hasWon = true;
}

char GameMechs::getUserInput() const
{
    return userInput;
}

void GameMechs::setUserInput(char input)
{
    userInput = input;
}

void GameMechs::resetUserInput()
{
    userInput = 0;
}

int GameMechs::getBoardWidth() const
{
    return boardWidth;
}

int GameMechs::getBoardHeight() const
{
    return boardHeight;
}

int GameMechs::getCurrentScore() const
{
    return currentScore;
}

void GameMechs::updateScore(int currentLength)
{
    currentScore = currentLength - 1;
}