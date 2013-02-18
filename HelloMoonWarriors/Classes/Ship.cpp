//
//  Ship.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "Ship.h"
#include "ResourcePath.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"


using namespace cocos2d;
using namespace CocosDenshion;


Ship::Ship()
{
    //init vars
    zOrder = 3000;
    appearPosition = ccp(160, 60);
    bulletSpeed = 900;
    active = true;
    hp = 1;
    timeTick = 0;
    hurtColorLife = 0;
    canBeAttack = true;
    
    //init life
    CCTexture2D *shipTexture = CCTextureCache::sharedTextureCache()->addImage(s_ship01);
    this->initWithTexture(shipTexture, CCRectMake(0, 0, 60, 38));
    this->setTag(this->zOrder);
    this->setPosition(this->appearPosition);
    
    //set frame
    CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(shipTexture, CCRectMake(0, 0, 60, 38));
    CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(shipTexture, CCRectMake(60, 0, 60, 38));

    CCArray *animFrames = CCArray::create();
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    
    //ship animate
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrame(frame0);
    animation->addSpriteFrame(frame1);
    //CCAnimation *animation = CCAnimation::create(animFrames, 0.1);
    CCAnimate *animate = CCAnimate::create(animation);
    this->runAction(CCRepeatForever::create(animate));
    
    this->schedule(schedule_selector(Ship::shoot), 0.17);
    
    // revive effect
    this->canBeAttack = false;
    CCSprite *ghostSprite = CCSprite::createWithTexture(shipTexture, CCRectMake(0, 45, 60, 38));
    ccBlendFunc bf = { GL_SRC_ALPHA, GL_ONE };
    ghostSprite->setBlendFunc(bf);
    ghostSprite->setScale(8);
    ghostSprite->setPosition(ccp(this->getContentSize().width/2, 12));
    this->addChild(ghostSprite);
    ghostSprite->runAction(CCScaleTo::create(0.5, 1, 1));
    CCBlink *blinks = CCBlink::create(3, 9);
    CCCallFunc *remove = CCCallFunc::create(ghostSprite, callfunc_selector(CCNode::removeFromParent));
    CCCallFunc *makeBeAttack = CCCallFunc::create(this, callfunc_selector(Ship::makeMeAttackCallback));
    this->runAction(CCSequence::create(CCDelayTime::create(0.5), blinks, makeBeAttack, remove, NULL));
}

void Ship::makeMeAttackCallback()
{
    this->canBeAttack = true;
    this->setVisible(true);
}

void Ship::update(float dt)
{
    if (this->hp <= 0) {
        this->active = false;
    }
    this->timeTick += dt;
    if (this->timeTick > 0.1) {
        this->timeTick = 0;
        if (this->hurtColorLife > 0) {
            this->hurtColorLife--;
        }
        if (this->hurtColorLife == 1) {
            this->setColor(ccWHITE);
        }
    }
}

void Ship::destroy()
{
    MW_LIFE--;
    CCPoint p = this->getPosition();
    CCNode *parent = this->getParent();
    // explosion
    parent->removeChild(this, true);
    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->playEffect(s_shipDestroyEffect);
    }
}

void Ship::shoot()
{
    int offset = 13;
    CCPoint p = this->getPosition();
    CCSize cs = this->getContentSize();
    
    Bullet *a = new Bullet(this->bulletSpeed, "W1.png", NORMAL);
    GameConfig::GetInstance()->MW_CONTAINER_PLAYER_BULLETS->addObject(a);
    this->getParent()->addChild(a, a->zOrder, PLAYER_BULLET);
    a->setPosition(ccp(p.x + offset, p.y + 3 + cs.height * 0.3));
    
    Bullet *b = new Bullet(this->bulletSpeed, "W1.png", NORMAL);
    GameConfig::GetInstance()->MW_CONTAINER_PLAYER_BULLETS->addObject(b);
    this->getParent()->addChild(b, b->zOrder, PLAYER_BULLET);
    b->setPosition(ccp(p.x - offset, p.y + 3 + cs.height * 0.3));
}

CCRect Ship::collideRect()
{
    CCPoint p = this->getPosition();
    CCSize a = this->getContentSize();
    return CCRectMake(p.x - a.width/2, p.y - a.height/2, a.width, a.height/2);
}

void Ship::hurt()
{
    if (this->canBeAttack) {
        this->hurtColorLife = 2;
        this->hp--;
        this->setColor(ccRED);
    }
}

