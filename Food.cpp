#include "Food.h"
//#include "MacUILib.h"
#include "GameMechs.h"
#include "objPos.h"
#include "Player.h"
//: foodPos(foodPos), playerPos(playerPos)
Food::Food()
{

    foodPos.setObjPos(-1, -1, 'o');
}

Food::~Food()
{
    //destruct
}

void Food::generateFood(objPos blockOff)
{
    srand(time(0));

    do 
    {
        foodPos.x=rand() % 30;
        foodPos.y=rand() % 15;
    }
    while(foodPos.isPosEqual(&blockOff));
    foodPos.symbol='o';


}

     
    //random 
    //is position equal



void Food::getFoodPos(objPos& returnPos)
{
    returnPos= foodPos;
   

}
