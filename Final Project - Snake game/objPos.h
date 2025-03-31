#ifndef OBJPOS_H
#define OBJPOS_H

// A simple structure for position
typedef struct 
{
    int x; // X-coordinate
    int y; // Y-coordinate
} Pos;

class objPos
{
public:
    Pos* pos;        // Pointer to pos structure
    char symbol;     // Symbol representing the object

    // Constructors and Destructor
    objPos();                               // Default Constructor
    objPos(int xPos, int yPos, char sym);   // Parameterized Constructor
    objPos(const objPos &a);                // Copy Constructor
    objPos& operator=(const objPos &a);     // Copy Assignment Operator
    ~objPos();                              // Destructor

    // Methods to manipulate object position
    void setObjPos(const objPos& o);        // Set position using another objPos
    void setObjPos(int xPos, int yPos, char sym); // Set position explicitly

    // Getters
    objPos getObjPos() const;               // Get a copy of this pos
    char getSymbol() const;                 // Get the symbol
    char getSymbolIfPosEqual(const objPos* refPos) const; // Get symbol if pos match

    // Comparison
    bool isPosEqual(const objPos* refPos) const; // Compare pos
};

#endif