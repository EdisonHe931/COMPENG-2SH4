#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
#include <iostream>

class Player
{   
public:
    // Enum for direction states
    enum Direction { UP, DOWN, LEFT, RIGHT, STOP }; 

    // Constructors and Destructor
    Player(); 
    Player(GameMechs* gameMechanics, Food* food);
    ~Player(); 
    Player(const Player& other);             // Copy constructor
    Player& operator=(const Player& other);  // Copy assignment operator

    // Player Movement and Behavior
    objPosArrayList* getPlayerPos() const;   // Get current pos
    void updatePlayerDir();                  // Update direction
    void movePlayer();                       // Move snake
    bool checkFoodConsumption();             // Check if food is consumed
    void increasePlayerLength();             // Increase snake size
    bool checkselfcollision();               // Check if snake eats itself

    // Speed Control
    int getSpeed() const; 
    void setSpeed(int speed);        

    // Food Management
    Food* getFoodlist() const;               // Get food object reference

private:
    objPosArrayList* player;   // List of snake body pos
    char headsymbol;           // Snake head
    char bodysymbol;           // Snake body
    Direction myDir;           // Movement direction

    Food* foodlist;            // Pointer to the food object
    GameMechs* mainGameMechsRef; // Pointer to game mechanics

    int rowNums;               // board height
    int colNums;               // board width
    int speed;                 // snake speed
};

#endif