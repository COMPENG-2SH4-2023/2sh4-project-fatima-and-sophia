#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList();
    playerPosList.insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList*  Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    if (mainGameMechsRef->getInput()) //does saying this makes sense? im trying to say that there is input presence
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
    playerPosList.getHeadElement(currHead)
    
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
            if(currHead.y >= mainGameMechsRef->getBoardSizeY())
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
            if(currHead.x >= mainGameMechsRef->getBoardSizeX())
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
}
