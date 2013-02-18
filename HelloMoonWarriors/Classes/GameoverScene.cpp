
//
//  GameoverScene.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#include "GameoverScene.h"
#include "ResourcePath.h"
#include "FlareEffect.h"
#include "GameScene.h"
#include "GameControlMenu.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


CCScene* GameoverLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameoverLayer *layer = GameoverLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameoverLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSprite *sp = CCSprite::create(s_loading);
    sp->setAnchorPoint(ccp(0, 0));
    this->addChild(sp, 0, 1);
    
    CCSprite *logo = CCSprite::create(s_gameover);
    logo->setAnchorPoint(ccp(0, 0));
    logo->setPosition(ccp(0, 300));
    this->addChild(logo, 10, 1);
    
    CCSprite *playAgainNormal = CCSprite::create(s_menu, CCRectMake(378, 0, 126, 33));
    CCSprite *playAgainSelected = CCSprite::create(s_menu, CCRectMake(378, 33, 126, 33));
    CCSprite *playAgainDisabled = CCSprite::create(s_menu, CCRectMake(378, 33*2, 126, 33));
    
    CCSprite *cocos2dhtml5 = CCSprite::create(s_cocos2dhtml5);
    cocos2dhtml5->setPosition(ccp(160, 150));
    this->addChild(cocos2dhtml5);
    CCMenuItemSprite *playAgain = CCMenuItemSprite::create(playAgainNormal, playAgainSelected, playAgainDisabled, this, menu_selector(GameoverLayer::playAgainCallback));
    
    CCMenu *menu = CCMenu::create(playAgain, NULL);
    this->addChild(menu, 1, 2);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    menu->setPosition(ccp(size.width/2, 220));
    
    finalScoreLabel = new char[40];
    sprintf(finalScoreLabel, "Your Score: %d", MW_SCORE);
    CCLabelTTF *lbScore = CCLabelTTF::create(this->finalScoreLabel, "Arial Bold", 16);
    lbScore->setPosition(ccp(160, 280));
    lbScore->setColor(ccc3(250, 179, 0));
    this->addChild(lbScore, 10);
    
    CCLabelTTF *b1 = CCLabelTTF::create("Download Cocos2d-html5", "Arial", 14);
    CCLabelTTF *b2 = CCLabelTTF::create("Download This Sample", "Arial", 14);
    
    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_mainMainMusic);
    }
    
    return true;
}

void GameoverLayer::playAgainCallback()
{
    flareEffect(this, callfunc_selector(GameoverLayer::onPlayAgain));
}

void GameoverLayer::onPlayAgain()
{
    CCScene *scene = CCScene::create();
    scene->addChild(GameLayer::create());
    scene->addChild(GameControlMenuLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
}

GameoverLayer::~GameoverLayer()
{
    if (finalScoreLabel != NULL) {
        delete[] finalScoreLabel;
        finalScoreLabel = NULL;
    }
}