//
//  Enemy.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#ifndef __HelloMoonWarriors__Enemy__
#define __HelloMoonWarriors__Enemy__

#include <iostream>
#include "cocos2d.h"
#include "GameConfig.h"
#include "EnemyType.h"

using namespace cocos2d;

class Enemy : public CCSprite
{
private:
    int hp;
    MW_ENEMY_ATTACK_MODE attackMode;
    int scoreValue;
    
    float delayTime;
    int bulletSpeed;
    float timeTick;
    int hurtColorLife;
    
    void shoot();
        
public:
    int zOrder;
    MW_ENEMY_MOVE_TYPE moveType;
    bool active;
    
    static void sharedEnemy();
    Enemy(EnemyType);
    void actionComplete(); // callback in levelmgr
    CCRect collideRect();
    void hurt();
    void destroy();
    void update(float);
};


#endif /* defined(__HelloMoonWarriors__Enemy__) */
