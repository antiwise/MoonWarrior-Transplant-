//
//  Level.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#include "Level.h"

LevelConst* LevelConst::_instance;

LevelConst* LevelConst::GetInstance()
{
    if (_instance == NULL) {
        _instance = new LevelConst();
    }
    return _instance;
}

LevelConst::LevelConst()
:enemyNum(2)
{
    enemies[0].ShowType = "Repeate";
    enemies[0].ShowTime = 2;
    enemies[0].TypeNum = 3;
    enemies[0].Types[0] = 0;
    enemies[0].Types[1] = 1;
    enemies[0].Types[2] = 2;
    
    enemies[1].ShowType = "Repeate";
    enemies[1].ShowTime = 5;
    enemies[1].TypeNum = 3;
    enemies[1].Types[0] = 3;
    enemies[1].Types[1] = 4;
    enemies[1].Types[2] = 5;
}

LevelConst::~LevelConst()
{
    
}

