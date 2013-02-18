//
//  Enemy.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#include "Enemy.h"
#include "ResourcePath.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "GameConfig.h"
#include "FlareEffect.h"

using namespace cocos2d;
using namespace CocosDenshion;

Enemy::Enemy(EnemyType enemyType)
{
    this->zOrder = 1000;
    this->bulletSpeed = -200;
    this->active = true;
    this->timeTick = 0;
    
    this->hp = enemyType.hp;
    this->scoreValue = enemyType.scoreValue;
    this->moveType = enemyType.moveType;
    this->attackMode = enemyType.attackMode;
    this->initWithSpriteFrameName(enemyType.textureName);
    
    this->delayTime = 1 + 1.2 * rand() / double(RAND_MAX);
    this->schedule(schedule_selector(Enemy::shoot), this->delayTime);
}

void Enemy::shoot()
{
    CCPoint p = this->getPosition();
    Bullet *bullet = new Bullet(this->bulletSpeed, "W2.png", NORMAL);
    GameConfig::GetInstance()->MW_CONTAINER_ENEMY_BULLETS->addObject(bullet);
    this->getParent()->addChild(bullet, this->zOrder, ENEMEY_BULLET);
    bullet->setPosition(ccp(p.x, p.y - this->getContentSize().height * 0.2));
}

void Enemy::update(float dt)
{
    if (this->hp <= 0) {
        this->active = false;
    }
    //?
    timeTick += dt;
    if (timeTick > 0.1) {
        this->timeTick = 0;
        if (this->hurtColorLife > 0) {
            this->hurtColorLife--;
        }
        if (this->hurtColorLife == 1) {
            this->setColor(ccWHITE);
        }
    }
}

void Enemy::actionComplete()
{
    CCDelayTime *a2 = CCDelayTime::create(1);
    CCMoveBy *a3 = CCMoveBy::create(1, ccp(100 + 100 * rand() / double(RAND_MAX), 0));
    this->runAction(CCRepeatForever::create(CCSequence::create(a2, a3, a2->copy(), a3->reverse(), NULL)));
}

CCRect Enemy::collideRect()
{
    CCSize a = this->getContentSize();
    CCPoint p = this->getPosition();
    return CCRectMake(p.x - a.width/2, p.y - a.height/4, a.width, a.height/2);
}

void Enemy::hurt()
{
    this->hurtColorLife = 2; //?
    this->hp--;
    this->setColor(ccRED);
}

void Enemy::destroy()
{
    MW_SCORE += this->scoreValue;
    //explosion
    
    spark(this->getPosition(), this->getParent(), 0.9, 0.4);
    GameConfig::GetInstance()->MW_CONTAINER_ENEMY->removeObject(this);
    this->removeFromParentAndCleanup(true);
    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->playEffect(s_explodeEffect);
    }
}

void Enemy::sharedEnemy()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_enemy_plist, s_enemy);
}