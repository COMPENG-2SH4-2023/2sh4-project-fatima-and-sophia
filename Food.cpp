#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


Food::Food()
{
    foodBucket=nullptr;
    foodPos.setObjPos(-1, -1, 'o');
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* playerPosList)
{
    int x = 30;
    int y = 15;
    srand(time(0));
  
    foodBucket = new objPosArrayList;
    char symbol;

    for (int j = 0; j < 3; j++)
    {
        bool occupied;
        objPos tempPos;
        objPos generatedPos;

        do
        {
            occupied = false;

            // Generate random position for food
            generatedPos.x = rand() % (x-2)+1;
            generatedPos.y = rand() % (y-2)+1;

            // Check if the generated position is occupied by the player
            for (int i = 0; i < playerPosList->getSize(); i++)
            {
                playerPosList->getElement(tempPos, i);
                if (generatedPos.isPosEqual(&tempPos))
                {
                    occupied = true;
                    break;
                }
            }
        } while (occupied);

        // Generate random symbol for food
        int actualSymbol = rand() % 3;
        switch (actualSymbol)
        {
        case 0:
            symbol = 'X';
            break;
        case 1:
            symbol = '0';
            break;
        default:
            symbol = 'o';
            break;
        }


        // Add the current food position to the foodBucket
        foodPos=generatedPos;

        objPos foodSymbolPos(generatedPos.x, generatedPos.y, symbol);
        foodBucket->insertTail(foodSymbolPos);

      
    }
}


objPosArrayList* Food:: getFoodBucket()
{
    return foodBucket;
}

void Food::getFoodPos(objPos& returnPos)
{
    returnPos = foodPos;
}
