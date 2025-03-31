#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// Global Variables
GameMechs* gameMechanics = nullptr;
Food* food = nullptr;
Player* player = nullptr;
bool exitFlag = false;

// Function Prototypes
void Initialize();
void GetInput();
void RunLogic();
void DrawScreen();
void LoopDelay();
void CleanUp();

int main()
{
    Initialize();

    // Main game loop
    while (!exitFlag && !gameMechanics->hasLostGame() && !gameMechanics->hasWonGame())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
        exitFlag = gameMechanics->hasExitedGame();
    }

    CleanUp();
    return 0;
}

void Initialize()
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Initialize game components
    gameMechanics = new GameMechs(15, 30); // Board size: 15x30
    food = new Food();
    player = new Player(gameMechanics, food);

    // Generate initial food
    food->generateFood(*player->getPlayerPos(), gameMechanics->getBoardWidth(), gameMechanics->getBoardHeight());

    exitFlag = false;
}

void GetInput()
{
    if (MacUILib_hasChar())
    {
        // Get input and update direction
        gameMechanics->setUserInput(MacUILib_getChar());
        player->updatePlayerDir();
        gameMechanics->resetUserInput();
    }
}

void RunLogic()
{
    // Move player and handle game logic
    player->movePlayer();
}

void DrawScreen()
{
    MacUILib_clearScreen();

    // Create board array
    char board[gameMechanics->getBoardWidth()][gameMechanics->getBoardHeight()] = {};

    for (int i = 0; i < gameMechanics->getBoardWidth(); i++)
    {
        for (int j = 0; j < gameMechanics->getBoardHeight(); j++)
        {
            // Draw borders
            if (i == 0 || i == gameMechanics->getBoardWidth() - 1 || j == 0 || j == gameMechanics->getBoardHeight() - 1)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' '; // Empty space
            }

            // Draw player
            for (int k = 0; k < player->getPlayerPos()->getSize(); k++)
            {
                if (i == player->getPlayerPos()->getElement(k).pos->x && j == player->getPlayerPos()->getElement(k).pos->y)
                {
                    board[i][j] = player->getPlayerPos()->getElement(k).symbol;
                }
            }

            // Draw food
            for (int k = 0; k < FOOD_SPAWN_CAP; k++)
            {
                if (i == food->getFoodPos(k).pos->x && j == food->getFoodPos(k).pos->y)
                {
                    // Oscillate special food
                    if (k == 3 && food->specialfoodcheck())
                    {
                        board[i][j] = food->getfoodoscillator() ? food->getspecial() : food->getnormal();
                        food->switchoscillator();
                    }
                    else
                    {
                        board[i][j] = food->getFoodPos(k).getSymbol();
                    }
                }
            }
        }
    }

    // Print the board
    for (int i = 0; i < gameMechanics->getBoardWidth(); i++)
    {
        for (int j = 0; j < gameMechanics->getBoardHeight(); j++)
        {
            MacUILib_printf("%c", board[i][j]);
        }
        MacUILib_printf("\n");
    }

    // Display messages
    if (!gameMechanics->hasLostGame() && !gameMechanics->hasExitedGame() && !gameMechanics->hasWonGame())
    {
        MacUILib_printf("Current Score: %d\n", gameMechanics->getCurrentScore());
        MacUILib_printf("Control the snake with 'W', 'A', 'S', 'D'.\n");
        MacUILib_printf("Special Food = More points!!!\n");
    }
    else if (gameMechanics->hasLostGame())
    {
        MacUILib_printf("Uh-Oh! Better luck next time!\n");
        MacUILib_printf("Final score: %d\n", gameMechanics->getCurrentScore());
    }
    else if (gameMechanics->hasWonGame())
    {
        MacUILib_printf("Great job! You won!\n");
        MacUILib_printf("Final score: %d\n", gameMechanics->getCurrentScore());
    }
    else if (gameMechanics->hasExitedGame())
    {
        MacUILib_printf("Thanks for playing!\n");
    }
}
void LoopDelay(void){
    MacUILib_Delay(DELAY_CONST/player -> getSpeed());
}

void CleanUp()
{
    int finalScore = gameMechanics->getCurrentScore();
    MacUILib_printf("Thank you for playing!\n");
    MacUILib_printf("Final score: %d\n", finalScore);

    // Free resources
    delete gameMechanics;
    delete food;
    delete player;

    MacUILib_clearScreen();
    MacUILib_uninit();
}