//
//  GameConfig.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__GameConfig__
#define __HelloMoonWarriors__GameConfig__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;



extern bool MW_SOUND;
extern int MW_SCORE;
extern int MW_LIFE;

enum MW_ENEMY_MOVE_TYPE
{
    ATTACK = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
    OVERLAP = 3,
};

enum MW_ENEMY_ATTACK_MODE
{
    NORMAL = 1,
    TSUIHIKIDAN = 2,
};

enum MW_UNIT_TAG
{
    ENEMEY_BULLET = 900,
    PLAYER_BULLET = 901,
    ENEMY = 1000,
    PLAYER = 1000
};

class GameConfig
{
private:
    GameConfig();
    virtual ~GameConfig();
    static GameConfig *_instance;
    
    
public:
    static GameConfig* GetInstance();
    CCArray *MW_CONTAINER_PLAYER_BULLETS;
    CCArray *MW_CONTAINER_ENEMY_BULLETS;
    CCArray *MW_CONTAINER_ENEMY;
    void ResetArray();
};

#endif /* defined(__HelloMoonWarriors__GameConfig__) */
