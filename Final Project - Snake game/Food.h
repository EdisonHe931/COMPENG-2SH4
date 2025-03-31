#ifndef FOOD_H
#define FOOD_H

#define FOOD_SPAWN_CAP 5 // Define max food items

#include "objPos.h"
#include "objPosArrayList.h"
#include <vector>

class Food
{
private:
    objPos* foodList; // Array of food positions
    int capacity;     // Maximum number of food items
    bool oscillator;  // Food oscillation state
    bool isSpecialFood; // Flag for special food presence
    char normalFoodSymbol; // Symbol for normal food
    char specialFoodSymbol; // Symbol for special food

public:
    // Constructors and Destructor
    Food();
    ~Food();
    Food(const Food& otherFood); // Copy Constructor
    Food& operator=(const Food& otherFood); // Copy Assignment Operator

    // Food generation
    void generateFood(const objPosArrayList& playerPositions, int boardWidth, int boardHeight);

    // Food retrieval
    objPos getFoodPos(int index) const;
    objPos getFoodPos(int x, int y) const;

    // Oscillator functions
    void switchoscillator();
    bool getfoodoscillator() const;

    // Special food checks
    bool specialfoodcheck();
    char getnormal();
    char getspecial();
};

#endif