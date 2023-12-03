#include "Food.h"


//#include "MacUILib.h"


//: foodPos(foodPos), playerPos(playerPos)
Food::Food()
{

    foodPos.setObjPos(-1, -1, 'o');
}

Food::~Food()
{
    //destruct
}

void Food::generateFood(objPosArrayList* playerPosList)
{
    int x=30;
    int y=15;
    bool occupied;
    srand(time(0));

    do 
    {
        foodPos.x=rand() % (x-2)+1;
        foodPos.y=rand() % (y-2)+1;
    

    occupied=false;
    objPos tempPos;
        for(int i=1; i<playerPosList->getSize(); i++)
        {
            playerPosList->getElement(tempPos, i);
            if (foodPos.isPosEqual(&tempPos))
            {
                occupied=true;
                break;
            }
        }
    }
    while(occupied);
    


}

     
    //random 
    //is position equal



void Food::getFoodPos(objPos& returnPos)
{
    returnPos = foodPos;
}
