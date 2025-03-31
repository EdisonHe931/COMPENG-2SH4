#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeArray = 200;
    aList = new objPos[sizeArray];
    arrayCapacity = 0;
}

objPosArrayList::objPosArrayList(int size)
{
    if(size < 1)sizeArray = 200;
    else
    {
        sizeArray = size;
    }
    aList = new objPos[sizeArray];
    arrayCapacity = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}
objPosArrayList::objPosArrayList(const objPosArrayList &other)
{
    sizeArray=other.sizeArray;
    aList=other.aList;
    arrayCapacity = other.arrayCapacity;
}
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &other)
{
    this->sizeArray = other.sizeArray;
    this->arrayCapacity = other.arrayCapacity;

    delete[] aList;
    aList = new objPos[sizeArray];
}
int objPosArrayList::getSize() const
{
    return arrayCapacity;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    
    for(int i = arrayCapacity-1; i >= 0; i--)
    {
        aList[i+1] = aList[i];
    }
    aList[0] = thisPos;
    arrayCapacity++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[arrayCapacity] = thisPos;
    arrayCapacity++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < arrayCapacity-1; i++)
    {
        aList[i] = aList[i+1];
    }
    aList[arrayCapacity-1].~objPos(); 
    arrayCapacity--;
}

void objPosArrayList::removeTail()
{
    aList[arrayCapacity-1].~objPos(); 
    arrayCapacity--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[arrayCapacity-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}