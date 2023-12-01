#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0; //no data at first 
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    for(int i = sizeList; i > 0; i--)   
        aList[i] = aList[i - 1];  // shuffling towards the tail

    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[sizeList++] = thisPos;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i + 1];  // shuffling towards the head
    } 
    sizeList--;
}

void objPosArrayList::removeTail()
{
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = aList[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = aList[sizeList - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = aList[index];
}
