#include "Food.h"
#include <cstdlib>
#include <time.h>
#include <vector>

// Constructor
Food::Food()
{
    capacity = FOOD_SPAWN_CAP; // Max num of food items
    foodList = new objPos[capacity];
    oscillator = true;
    isSpecialFood = false;
    normalFoodSymbol = 'o';
    specialFoodSymbol = 'O';
}

// Destructor
Food::~Food()
{
    delete[] foodList;
}

// Copy Constructor
Food::Food(const Food& otherFood)
{
    capacity = otherFood.capacity;
    foodList = new objPos[capacity];
    for (int i = 0; i < capacity; i++)
    {
        foodList[i] = otherFood.foodList[i];
    }
    oscillator = otherFood.oscillator;
    isSpecialFood = otherFood.isSpecialFood;
    normalFoodSymbol = otherFood.normalFoodSymbol;
    specialFoodSymbol = otherFood.specialFoodSymbol;
}

// Copy Assignment Operator
Food& Food::operator=(const Food& otherFood)
{
    if (this != &otherFood)
    {
        delete[] foodList;
        capacity = otherFood.capacity;
        foodList = new objPos[capacity];
        for (int i = 0; i < capacity; i++)
        {
            foodList[i] = otherFood.foodList[i];
        }
        oscillator = otherFood.oscillator;
        isSpecialFood = otherFood.isSpecialFood;
        normalFoodSymbol = otherFood.normalFoodSymbol;
        specialFoodSymbol = otherFood.specialFoodSymbol;
    }
    return *this;
}

// Generate Food
void Food::generateFood(const objPosArrayList& playerPositions, int boardWidth, int boardHeight)
{
    srand(time(NULL));

    // 2D vector to represent available spots
    std::vector<std::vector<int>> boardAvailability(boardHeight, std::vector<int>(boardWidth, 0));

    // Mark taken spots based on current location
    for (int i = 0; i < playerPositions.getSize(); i++)
    {
        boardAvailability[playerPositions.getElement(i).pos->y][playerPositions.getElement(i).pos->x] = 1;
    }

    // Generate food 
    for (int i = 0; i < capacity; i++)
    {
        int x, y;
        do
        {
            x = rand() % (boardWidth - 2) + 1; // Rand pos
            y = rand() % (boardHeight - 2) + 1;
        } while (boardAvailability[y][x] != 0); // Ensure the pos is not taken

        // Assign food symbol: Special food for index 3 with a 50% chance
        if (i == 3 && rand() % 2 == 0)
        {
            foodList[i].setObjPos(x, y, specialFoodSymbol);
            isSpecialFood = true;
        }
        else
        {
            foodList[i].setObjPos(x, y, normalFoodSymbol);
        }

        boardAvailability[y][x] = 1; // Mark pos as taken
    }
}

// Get food pos by index
objPos Food::getFoodPos(int index) const
{
    if (index >= 0 && index < capacity)
    {
        return foodList[index];
    }
    return objPos(0, 0, ' ');
}

// Get food pos by coordinates
objPos Food::getFoodPos(int x, int y) const
{
    for (int i = 0; i < capacity; i++)
    {
        if (foodList[i].pos->x == x && foodList[i].pos->y == y)
        {
            return foodList[i];
        }
    }
    return objPos(0, 0, ' ');
}

// Oscillator Functions
void Food::switchoscillator()
{
    oscillator = !oscillator;
}

bool Food::getfoodoscillator() const
{
    return oscillator;
}

// Check what type of food it is (Special or regular)
bool Food::specialfoodcheck()
{
    return isSpecialFood;
}

// Get normal and special symbols
char Food::getnormal()
{
    return normalFoodSymbol;
}

char Food::getspecial()
{
    return specialFoodSymbol;
}