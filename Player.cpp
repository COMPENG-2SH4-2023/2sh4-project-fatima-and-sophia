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

    if (mainGameMechsRef->getInput()!= 0) 
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


}

void Player::increasePlayerLength(char foodType)
{
    objPos currTail;
    playerPosList->getTailElement(currTail);


    objPos addNew;
    addNew.setObjPos(currTail.x,currTail.y, '*');

    switch (foodType)
    {
        case '0':
            playerPosList->insertTail(addNew);
            playerPosList->insertTail(addNew);
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->incrementScore();
            break;

        case 'o':
            playerPosList->insertTail(addNew);
            mainGameMechsRef->incrementScore();
            break;

        case 'X':
            if(playerPosList->getSize() > 1)
            {
                playerPosList->removeTail();
                mainGameMechsRef->decrementScore();
            }
            break;
        default:
            break;

    }
   
}


bool Player::checkSelfCollision()
{
    objPos headPos;
    playerPosList->getHeadElement(headPos);
    

    int i = 2;
    while (i < playerPosList->getSize())
    {
        objPos bodyPos;
        playerPosList->getElement(bodyPos, i);
        if(headPos.isPosEqual(&bodyPos))
        {
            return true;
        }
        i++;
    }
    return false;
    
}
