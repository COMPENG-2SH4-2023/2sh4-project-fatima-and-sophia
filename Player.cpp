#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"

#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"





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





    // if (myDir==UP)
    // {
    //      playerPos.y--;
    //      moveCount++;
    // }
    // else if (myDir==DOWN)
    // {
    //     playerPos.y++;
    //     moveCount++;
    // }
    // else if (myDir==LEFT)
    // {
    //     playerPos.x--;
    //     moveCount++;
    // }
    // else if (myDir==RIGHT)
    // {
    //     playerPos.x++;
    //     moveCount++;
    // }

    // //Border wraparound 
    // if (playerPos.x<0)
    // {
    //     playerPos.x = mainGameMechsRef->getBoardSizeX()-1;
    // }
    // else if (playerPos.x >= mainGameMechsRef->getBoardSizeX())
    // {
    //     playerPos.x = 0;
    // }
    // else if (playerPos.x >= mainGameMechsRef->getBoardSizeX())
    // {
    //     playerPos.x = 0;
    // }
    // else if (playerPos.y<0)
    // {
    //     playerPos.y = mainGameMechsRef->getBoardSizeY()-1;
    // }
    // else if (playerPos.y>=mainGameMechsRef->getBoardSizeY())
    // {
    //     playerPos.y = 0;
    // }
}

void Player::increasePlayerLength()
{
    objPos currTail;
    playerPosList->getTailElement(currTail);
    objPos addNew;
    addNew.setObjPos(currTail.x - 1, currTail.y - 1, '*');
    playerPosList->insertHead(addNew);
}

bool Player::checkFoodConsumption()
{

    objPos headPos;
    objPos foodPos;

    playerPosList->getHeadElement(headPos);
    getFoodPos(foodPos);
    return foodPos.isPosEqual(&headPos);
}
