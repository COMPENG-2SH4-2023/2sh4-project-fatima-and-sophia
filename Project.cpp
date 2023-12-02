#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000



GameMechs* myGM; //will need to delete because on heap
Player* myPlayer;
Food* myFood;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    //makeshift setup so i dont have to generate item yet need to do it yourself
    objPos tempPos(-1, -1, 'o');
    myFood->generateFood(tempPos); 
    
    

    
}

void GetInput(void)
{
      

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos bodyPos;
    playerBody->getHeadElement(bodyPos);

    objPos playerPos;
    myPlayer->getPlayerPos();

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    if (foodPos.x == bodyPos.x && foodPos.y == bodyPos.y||foodPos.x == -1 && foodPos.y== -1) 
    {
        myPlayer->increasePlayerLength();
        myFood->generateFood(playerPos);
    }
   

}

void DrawScreen()
{
   
    MacUILib_clearScreen();

    bool drawn;
    
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;


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

            if (i == 0 || i == myGM->getBoardSizeY()-1 || j == 0 || j == myGM->getBoardSizeX()-1)
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
        MacUILib_printf("\n");
    }  

    MacUILib_printf("Score: %d\n", myGM->getScore());   
    MacUILib_printf("Food Position: <%d, %d>", foodPos.x, foodPos.y);   



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
