#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"
#include <cstdlib>

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;
objPos tempPos;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    srand(time(0));

    Initialize();
    
    while(!myGM->getExitFlagStatus() && !myGM->getLoseFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();


    myGM = new GameMechs(30, 15);
    myPlayer = new Player(myGM);
    myFood = new Food();
    
    myFood->generateFood(myPlayer->getPlayerPos());
    
    
}

void GetInput(void)
{
    myGM->getInput();

}

void RunLogic(void)
{
   
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();


    if (!myPlayer->checkSelfCollision())
    {
        objPosArrayList* playerBody = myPlayer->getPlayerPos();
        objPos bodyPos;
        playerBody->getHeadElement(bodyPos);

    
        myPlayer->getPlayerPos();
        

        objPos foodPos;
        myFood->getFoodPos(foodPos);
    
        for (int i = 0; i < myFood->getFoodBucket()->getSize(); i++)
        {
            objPos tempFood;
            myFood->getFoodBucket()->getElement(tempFood, i);
    
            if (tempFood.x == bodyPos.x && tempFood.y == bodyPos.y)
            {
            
                myFood->generateFood(myPlayer->getPlayerPos());
                myPlayer->increasePlayerLength(tempFood.symbol);
        
            }
        }
    }
          
}
void DrawScreen()
{
    MacUILib_clearScreen();

    bool drawn;
    bool foodDrawn;
    
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos tempFood;

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;

            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue; //if player body was drawn don't draw anything below
            foodDrawn = false;
            for (int l = 0; l < myFood->getFoodBucket()->getSize(); l++)
            {
                myFood->getFoodBucket()->getElement(tempFood, l);
                if (j == tempFood.x && i == tempFood.y)
                {
                    MacUILib_printf("%c", tempFood.symbol);
                    foodDrawn = true;
                    break;
                }
            }
            if (!foodDrawn)
            {
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c",'#');
                }
        
                else if (j == foodPos.x && i == foodPos.y)
                {
                    
                    MacUILib_printf("%c", foodPos.symbol);
                }

                else
                {
                    MacUILib_printf("%c",' ');
                }
            }
        }
        MacUILib_printf("\n");
    }  

    MacUILib_printf("Score: %d\n", myGM->getScore());   
    for (int l = 0; l < myFood->getFoodBucket()->getSize(); l++)
    {
        myFood->getFoodBucket()->getElement(tempFood, l);
        MacUILib_printf("Food Position: <%d, %d>\n", tempFood.x, tempFood.y);
    }
    if (myPlayer->checkSelfCollision())
    {
        MacUILib_clearScreen();
        MacUILib_printf("Self-collided! Game over :(\nFinal Score: %d", myGM->getScore());
    }
    MacUILib_printf("Eat the o to increase snake body by one segment\n");
    MacUILib_printf("Eat the 0 to increase snake body by two segments\n");
    MacUILib_printf("Beware! X will shrink the snake by one segment\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM; //avoid memory leak
    delete myPlayer;
    delete myFood;
}
