#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H
#define ARRAY_MAX_CAP 200
#include "objPos.h"

class objPosArrayList
{
private:
    objPos* aList;       // Dynamic array to hold objPos objects
    int listSize;        // Current number of elements in the list
    int arrayCapacity;   // Maximum capacity of the array

public:
    static constexpr int MAX_CAPACITY = 200; // Maximum capacity of the array

    // Constructors and Destructor
    objPosArrayList();                            // Default Constructor
    ~objPosArrayList();                           // Destructor
    objPosArrayList(const objPosArrayList& array); // Copy Constructor
    objPosArrayList& operator=(const objPosArrayList& array); // Copy Assignment Operator

    // Getters
    int getSize() const; // Returns the current size of the list

    // Insertions
    void insertHead(objPos thisPos); // Insert at the head of the list
    void insertTail(objPos thisPos); // Insert at the tail of the list

    // Removals
    void removeHead(); // Remove the head element of the list
    void removeTail(); // Remove the tail element of the list

    // Accessors
    objPos getHeadElement() const; // Retrieve the head element
    objPos getTailElement() const; // Retrieve the tail element
    objPos getElement(int index) const; // Retrieve an element by index
};

#endif