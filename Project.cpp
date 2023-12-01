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
    

    
}

void GetInput(void)
{
      

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();

    objPos playerPos;
    myPlayer->getPlayerPos(playerPos);

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    if(foodPos.x ==playerPos.x && foodPos.y == playerPos.y||foodPos.x==-1&&foodPos.y==-1)
    {
        myFood->generateFood(playerPos);
    }
   

}

void DrawScreen()
{
   
    MacUILib_clearScreen();
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos); //get player position
    objPos foodPos;
    myFood->getFoodPos(foodPos);
    

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j= 0; j < myGM->getBoardSizeX(); j++)
        {
            if (i == 0 || i == myGM->getBoardSizeY()-1 || j == 0 || j == myGM->getBoardSizeX()-1)
            {
                MacUILib_printf("%c",'#');
            }
            else if (j == tempPos.x && i == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            else if (j==foodPos.x && i==foodPos.y)
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

    MacUILib_printf("Score: %d, Player Pos: <%d,%d>\n", myGM->getScore(), tempPos.x, tempPos.y);   



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
