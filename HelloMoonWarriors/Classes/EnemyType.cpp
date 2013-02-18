//
//  EnemyType.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#include "EnemyType.h"

EnemyTypeMgr* EnemyTypeMgr::_instance;

EnemyTypeMgr* EnemyTypeMgr::GetInstance()
{
    if (_instance == NULL) {
        _instance = new EnemyTypeMgr();
    }
    return _instance;
}

EnemyTypeMgr::EnemyTypeMgr()
{
    // 0
    enemyTypes[0].typeIdx = 0;
    enemyTypes[0].textureName = "E0.png";
    enemyTypes[0].bulletType = "W2.png";
    enemyTypes[0].hp = 1;
    enemyTypes[0].moveType = ATTACK;
    enemyTypes[0].attackMode = NORMAL;
    enemyTypes[0].scoreValue = 15;
    
    // 1
    enemyTypes[1].typeIdx = 1;
    enemyTypes[1].textureName = "E1.png";
    enemyTypes[1].bulletType = "W2.png";
    enemyTypes[1].hp = 2;
    enemyTypes[1].moveType = ATTACK;
    enemyTypes[1].attackMode = NORMAL;
    enemyTypes[1].scoreValue = 40;
    
    // 2
    enemyTypes[2].typeIdx = 2;
    enemyTypes[2].textureName = "E2.png";
    enemyTypes[2].bulletType = "W2.png";
    enemyTypes[2].hp = 4;
    enemyTypes[2].moveType = OVERLAP;
    enemyTypes[2].attackMode = NORMAL;
    enemyTypes[2].scoreValue = 80;
    
    // 3
    enemyTypes[3].typeIdx = 3;
    enemyTypes[3].textureName = "E3.png";
    enemyTypes[3].bulletType = "W2.png";
    enemyTypes[3].hp = 6;
    enemyTypes[3].moveType = OVERLAP;
    enemyTypes[3].attackMode = NORMAL;
    enemyTypes[3].scoreValue = 80;
    
    // 4
    enemyTypes[4].typeIdx = 4;
    enemyTypes[4].textureName = "E4.png";
    enemyTypes[4].bulletType = "W2.png";
    enemyTypes[4].hp = 10;
    enemyTypes[4].moveType = HORIZONTAL;
    enemyTypes[4].attackMode = TSUIHIKIDAN;
    enemyTypes[4].scoreValue = 150;
    
    // 5
    enemyTypes[5].typeIdx = 5;
    enemyTypes[5].textureName = "E5.png";
    enemyTypes[5].bulletType = "W2.png";
    enemyTypes[5].hp = 15;
    enemyTypes[5].moveType = HORIZONTAL;
    enemyTypes[5].attackMode = NORMAL;
    enemyTypes[5].scoreValue = 200;
}

EnemyTypeMgr::~EnemyTypeMgr()
{
    
}