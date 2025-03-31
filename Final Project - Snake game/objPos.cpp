#include "objPos.h"

// Default Constructor
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // NULL
}

// Parameterized Constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Copy Constructor
objPos::objPos(const objPos &a)
{
    pos = new Pos;
    pos->x = a.pos->x;
    pos->y = a.pos->y;
    symbol = a.symbol;
}

// Copy Assignment Operator
objPos& objPos::operator=(const objPos &a)
{
    if (this != &a)
    {
        // Free the existing resource
        delete pos;

        // Allocate new resource and copy data
        pos = new Pos;
        pos->x = a.pos->x;
        pos->y = a.pos->y;
        symbol = a.symbol;
    }
    return *this;
}

// Destructor
objPos::~objPos()
{
    delete pos;
}

// Set pos using another object
void objPos::setObjPos(const objPos& o) // Use const reference to avoid unnecessary copying
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Set Position using coordinnates and symbol
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Get the current pos object
objPos objPos::getObjPos() const
{
    return objPos(pos->x, pos->y, symbol); 
}

// Get symbol of current pos
char objPos::getSymbol() const
{
    return symbol;
}

// Check if this pos is equal to another pos
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Get the symbol if pos matches another one
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if (isPosEqual(refPos))
    {
        return symbol;
    }
    return 0; 
}