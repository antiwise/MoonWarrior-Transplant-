//
//  GameConfig.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "GameConfig.h"

using namespace cocos2d;

bool MW_SOUND = true;
int MW_SCORE = 0;
int MW_LIFE = 4;


GameConfig* GameConfig::_instance;

GameConfig* GameConfig::GetInstance()
{
    if (_instance == NULL) {
        _instance = new GameConfig();
    }
    return _instance;
}

GameConfig::GameConfig()
{
    MW_CONTAINER_PLAYER_BULLETS = CCArray::create();
    MW_CONTAINER_PLAYER_BULLETS->retain();
    
    MW_CONTAINER_ENEMY_BULLETS = CCArray::create();
    MW_CONTAINER_ENEMY_BULLETS->retain();
    
    MW_CONTAINER_ENEMY = CCArray::create();
    MW_CONTAINER_ENEMY->retain();
}

void GameConfig::ResetArray()
{
    MW_CONTAINER_PLAYER_BULLETS->removeAllObjects();
    MW_CONTAINER_ENEMY_BULLETS->removeAllObjects();
    MW_CONTAINER_ENEMY->removeAllObjects();
}

GameConfig::~GameConfig()
{
    MW_CONTAINER_PLAYER_BULLETS->release();
    MW_CONTAINER_ENEMY_BULLETS->release();
    MW_CONTAINER_ENEMY->release();
}