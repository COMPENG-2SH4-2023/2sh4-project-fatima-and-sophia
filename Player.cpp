#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"




Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY(), '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite State Machine logic

    int moveCount;
    moveCount++;


    //Update player location by one unit
    if (myDir==UP)
    {
         playerPos.y--;
         moveCount++;
    }
    else if (myDir==DOWN)
    {
        playerPos.y++;
        moveCount++;
    }
    else if (myDir==LEFT)
    {
        playerPos.x--;
        moveCount++;
    }
    else if (myDir==RIGHT)
    {
        playerPos.x++;
        moveCount++;
    }

    //Border wraparound 
    if (playerPos.x<0)
    {
        playerPos.x = mainGameMechsRef->getBoardSizeX()-1;
    }
    else if (playerPos.x >= mainGameMechsRef->getBoardSizeX())
    {
        playerPos.x = mainGameMechsRef->getBoardSizeX()-1;
    }
    else if (playerPos.x >= mainGameMechsRef->getBoardSizeX())

    {
        playerPos.x = 0;
    }
    else if (playerPos.y<0)
    {

        playerPos.y = mainGameMechsRef->getBoardSizeY()-1;
    }
    else if (playerPos.y>=mainGameMechsRef->getBoardSizeY())
    {

        playerPos.y = mainGameMechsRef->getBoardSizeY()-1;
    }
    else if (playerPos.y>=mainGameMechsRef->getBoardSizeY())

    {
        playerPos.y = 0;
    }
}
