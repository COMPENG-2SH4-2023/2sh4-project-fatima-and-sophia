#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <ctime>
#include <iostream>


#include "objPos.h"
//#include "MacUILib.h"



using namespace std;


class Food
{
    private:
        objPos foodPos;
     


       
    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
};

#endif
