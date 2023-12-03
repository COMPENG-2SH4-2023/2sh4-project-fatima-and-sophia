#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    if (mainGameMechsRef->getInput() != 0) //does saying this makes sense? im trying to say that there is input presence
    {
        switch(mainGameMechsRef->getInput())

        {                      
            case '^':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                if (myDir!=DOWN)
                {
                    myDir = UP;
                }
                break;
            case 's':
                if (myDir!=UP)
                {
                    myDir = DOWN;
                }
                break;
            case 'a':
                if (myDir!=RIGHT)
                {
                    myDir = LEFT;
                }
                break;
            case 'd':
                if (myDir!=LEFT)
                {
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }       
    }
}

void Player::movePlayer()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    //Update player location by one unit
    switch(myDir)
    {
        case UP:
            currHead.y--;
            if(currHead.y <= 0)
            {
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currHead.y++;
            if(currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            {
                currHead.y = 1;
            }
            break;

        case LEFT:
            currHead.x--;
            if(currHead.x <= 0)
            {
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            {
                currHead.x = 1;
            }
            break;
        
        case STOP:
        default:
            break; 
    }

    playerPosList->insertHead(currHead);

    playerPosList->removeTail();


    // if (foodPos.x == bodyPos.x && foodPos.y == bodyPos.y||foodPos.x == -1 && foodPos.y== -1) 
    // {
    //     increasePlayerLength();
    //     myFood->generateFood(playerPos);
    // }

}

/*bool Player::checkFoodConsumption()
{
    objPos headPos;
    

}*/
void Player::increasePlayerLength()
{
    objPos currTail;
    playerPosList->getTailElement(currTail);
    objPos addNew;
    addNew.setObjPos(currTail.x, currTail.y, '*');
    playerPosList->insertHead(addNew);
    
}

bool Player::checkSelfCollision()
{
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    objPos bodyPos;


    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(bodyPos, i);
        if (headPos.x == bodyPos.x && headPos.y == bodyPos.y)
        {
            return true;
        }
    }
    return false;
    
}


// {
//     objPos headPos;
//     objPos foodPos;

//     playerPosList->getHeadElement(headPos);
//     currentFood->getFoodPos(foodPos);

//     if (headPos.isPosEqual(&foodPos)) 
//     {
//         return true;
//     }
//     return false;
// }
