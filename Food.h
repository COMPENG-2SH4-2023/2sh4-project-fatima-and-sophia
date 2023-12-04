#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <iostream>


#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"


using namespace std;


class Food
{
    private:
        objPos foodPos;
        objPosArrayList* foodBucket;

     


       
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* playerPosList); 
        void getFoodPos(objPos &returnPos);
        objPosArrayList* getFoodBucket();
        
};

#endif
