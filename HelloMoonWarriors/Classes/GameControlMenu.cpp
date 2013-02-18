//
//  GameControlMenu.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "GameControlMenu.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "ResourcePath.h"
#include "CCSprite.h"
#include "HelloWorldScene.h"
#include "GameConfig.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameControlMenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameControlMenuLayer *layer = GameControlMenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameControlMenuLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont *pBackMainMenu = CCMenuItemFont::create("Main Menu", this, menu_selector(GameControlMenuLayer::menuCallback));
    CCMenu *pMenu = CCMenu::create(pBackMainMenu, NULL);

    pMenu->setPosition(ccp(0, 0));
    pBackMainMenu->setAnchorPoint(ccp(0, 0));
    pBackMainMenu->setPosition(ccp(size.width - 95, 5));
    this->addChild(pMenu, 1, 2);
    
    return true;
}

void GameControlMenuLayer::menuCallback(CCObject*)
{
    CCScene *pSysMenu = CCScene::create();
    pSysMenu->addChild(HelloWorld::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pSysMenu));
}