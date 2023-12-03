#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <iostream>


#include "objPos.h"
#include "objPosArrayList.h"
//class Player;
#include "Player.h"
//#include "MacUILib.h"



using namespace std;


class Food
{
    private:
        objPos foodPos;
     


       
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* playerPosList); //upgrade somehow
        void getFoodPos(objPos &returnPos);
};

#endif

