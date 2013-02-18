//
//  Bullet.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "Bullet.h"
#include "ResourcePath.h"

using namespace cocos2d;


Bullet::Bullet(int bulletSpeed, char *weaponType, MW_ENEMY_ATTACK_MODE attackMode)
{
    this->active = true;
    this->xVelocity = 0;
    this->yVelocity = 200;
    this->power = 1;
    this->hp = 1;
    this->zOrder = 3000;
    
    this->yVelocity = -bulletSpeed;
    this->attackMode = attackMode;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_bullet_plist);
    this->initWithSpriteFrameName(weaponType);
    ccBlendFunc bf = { GL_SRC_ALPHA, GL_ONE };
    this->setBlendFunc(bf);
}


void Bullet::update(float dt)
{
    CCPoint p = this->getPosition();
    p.x -= this->xVelocity * dt;
    p.y -= this->yVelocity * dt;
    this->setPosition(p);
    if (this->hp <= 0) {
        this->active = false;
    }
}

void Bullet::destroy()
{
    CCSprite *explode = CCSprite::create(s_hit);
    ccBlendFunc bf = { GL_SRC_ALPHA, GL_ONE };
    explode->setBlendFunc(bf);
    explode->setPosition(this->getPosition());
    explode->setRotation(rand() / double(RAND_MAX) * 360);
    explode->setScale(0.75);
    this->getParent()->addChild(explode, 9999);
    GameConfig::GetInstance()->MW_CONTAINER_PLAYER_BULLETS->removeObject(this);
    GameConfig::GetInstance()->MW_CONTAINER_ENEMY_BULLETS->removeObject(this);
    this->removeFromParentAndCleanup(true);
    CCCallFunc *removeExplode = CCCallFunc::create(explode, callfunc_selector(CCNode::removeFromParentAndCleanup));
    explode->runAction(CCScaleBy::create(0.3, 2.2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.3), removeExplode));
}

void Bullet::hurt()
{
    this->hp--;
}

CCRect Bullet::collideRect()
{
    CCPoint p = this->getPosition();
    return CCRectMake(p.x-3, p.y-3, 6, 6);
}
