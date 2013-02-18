//
//  Ship.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__Ship__
#define __HelloMoonWarriors__Ship__

#include <iostream>
#include "cocos2d.h"
#include "GameConfig.h"

using namespace cocos2d;

class Ship : public CCSprite
{
private:
    CCPoint appearPosition;
    int hp;
    int bulletSpeed;
    float timeTick;
    int hurtColorLife;
    bool canBeAttack;
    
    void shoot();
    void makeMeAttackCallback();
    
public:
    int zOrder;
    bool active;
    
    Ship();

    void update(float);
    void destroy();
    CCRect collideRect();
    void hurt();
};

#endif /* defined(__HelloMoonWarriors__Ship__) */
