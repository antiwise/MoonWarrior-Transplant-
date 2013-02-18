//
//  EnemyType.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#ifndef __HelloMoonWarriors__EnemyType__
#define __HelloMoonWarriors__EnemyType__

#include <iostream>
#include "GameConfig.h"

struct EnemyType {
    int typeIdx;
    char* textureName;
    char* bulletType;
    int hp;
    MW_ENEMY_MOVE_TYPE moveType;
    MW_ENEMY_ATTACK_MODE attackMode;
    int scoreValue;
};

class EnemyTypeMgr {
    
private:
    EnemyTypeMgr();
    virtual ~EnemyTypeMgr();
    static EnemyTypeMgr *_instance;
    
public:
    static EnemyTypeMgr* GetInstance();
    EnemyType enemyTypes[6];
    int typeNum;
};

#endif /* defined(__HelloMoonWarriors__EnemyType__) */
