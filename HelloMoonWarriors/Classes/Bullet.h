//
//  Bullet.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__Bullet__
#define __HelloMoonWarriors__Bullet__

#include <iostream>
#include "cocos2d.h"
#include "GameConfig.h"

using namespace cocos2d;

class Bullet : public CCSprite
{
private:
    int xVelocity;
    int yVelocity;
    int power;
    
    int hp;

    MW_ENEMY_ATTACK_MODE attackMode;
    
public:
    int zOrder;
    bool active;
    
    void update(float);
    void destroy();
    
    Bullet(int bulletSpeed, char *weaponType, MW_ENEMY_ATTACK_MODE attackMode);
    void hurt();
    CCRect collideRect();
};

#endif /* defined(__HelloMoonWarriors__Bullet__) */
