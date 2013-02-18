//
//  FlareEffect.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "FlareEffect.h"
#include "CCSprite.h"
#include "ResourcePath.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

void flareEffect(CCNode *parent, SEL_CallFunc callback)
{
    CCSprite *flareSprite = CCSprite::create(s_flare);
    ccBlendFunc bf = { GL_SRC_ALPHA, GL_ONE };
    flareSprite->setBlendFunc(bf);
    
    parent->addChild(flareSprite, 10);
    flareSprite->setOpacity(0);
    flareSprite->setPosition(ccp(-30, 297));
    flareSprite->setRotation(-120);
    flareSprite->setScale(0.2);
    
    CCFadeTo *pOpacityAnim = CCFadeTo::create(0.5, 255);
    CCFadeTo *pOpacDim = CCFadeTo::create(1, 0);
    CCScaleBy *pBiggeAnim = CCScaleBy::create(0.7, 1.2, 1.2);
    CCEaseSineOut *pBiggerEase = CCEaseSineOut::create(pBiggeAnim);
    CCMoveBy *pMoveAnim = CCMoveBy::create(0.5, ccp(328, 0));
    CCEaseSineOut *pEaseMove = CCEaseSineOut::create(pMoveAnim);
    CCRotateBy *pRotateAnim = CCRotateBy::create(2.5, 90);
    CCEaseExponentialOut *pRotateEase = CCEaseExponentialOut::create(pRotateAnim);
    CCScaleTo *pBigger = CCScaleTo::create(0.5, 1);
    
    CCCallFunc *pOnComplete = CCCallFunc::create(parent, callback);
    //CCCallFunc *pKillFlare = CCCallFunc::create(killFlareCallback);
    
    flareSprite->runAction(CCSequence::create(pOpacityAnim, pBiggerEase, pOpacDim, pOnComplete, NULL));
    flareSprite->runAction(pEaseMove);
    flareSprite->runAction(pRotateEase);
    flareSprite->runAction(pBigger);
    
}

void killFlareCallback(CCNode* sprite)
{
    sprite->removeFromParentAndCleanup(true);
}

void spark(CCPoint ccpoint, CCNode* parent, float scale, float duration)
{
    CCSprite *one = CCSprite::create(s_explode1);
    CCSprite *two = CCSprite::create(s_explode2);
    CCSprite *three = CCSprite::create(s_explode3);
    
    ccBlendFunc bf = { GL_SRC_ALPHA, GL_ONE };
    one->setBlendFunc(bf);
    two->setBlendFunc(bf);
    three->setBlendFunc(bf);
    
    one->setPosition(ccpoint);
    two->setPosition(ccpoint);
    three->setPosition(ccpoint);
    
    parent->addChild(one);
    parent->addChild(two);
    parent->addChild(three);
    
    one->setScale(scale);
    two->setScale(scale);
    three->setScale(scale);
    
    three->setRotation(rand() / double(RAND_MAX) * 360);
    
    CCRotateBy *left = CCRotateBy::create(duration, -45);
    CCRotateBy *right = CCRotateBy::create(duration, 45);
    CCScaleBy *scaleBy = CCScaleBy::create(duration, 3, 3);
    CCFadeOut *fadeOut = CCFadeOut::create(duration);
    CCCallFunc *remove1 = CCCallFunc::create(one, callfunc_selector(CCNode::removeFromParent));
    CCSequence *seq1 = CCSequence::create(fadeOut, remove1, NULL);
    
    CCCallFunc *remove2 = CCCallFunc::create(two, callfunc_selector(CCNode::removeFromParent));
    CCSequence *seq2 = CCSequence::create(fadeOut, remove2, NULL);
    
    CCCallFunc *remove3 = CCCallFunc::create(three, callfunc_selector(CCNode::removeFromParent));
    CCSequence *seq3 = CCSequence::create(fadeOut, remove3, NULL);
    
    one->runAction(left);
    two->runAction(right);
    
    one->runAction(scaleBy);
    two->runAction((CCAction*)(scaleBy->copy()));
    three->runAction((CCAction*)(scaleBy->copy()));
    
    one->runAction(seq1);
    two->runAction(seq2);
    three->runAction(seq3);
}