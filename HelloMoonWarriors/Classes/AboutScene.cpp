//
//  AboutScene.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-11.
//
//

#include "AboutScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "ResourcePath.h"
#include "CCSprite.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* AboutLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AboutLayer *layer = AboutLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool AboutLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // set background
    CCSprite *pBackGround = CCSprite::create(s_loading);
    pBackGround->setAnchorPoint(CCPointZero);
    this->addChild(pBackGround, 0, loadingTag);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // about title
    CCTexture2D *pMenuTitleTex = CCTextureCache::sharedTextureCache()->addImage(s_menuTile);
    CCSprite *pTitle = CCSprite::createWithTexture(pMenuTitleTex, CCRectMake(0, 36, 100, 34));
    pTitle->setPosition(ccp(size.width / 2, size.height - 60));
    this->addChild(pTitle);
    
    // literal label
    CCLabelTTF *pLabel = CCLabelTTF::create("   This showcase utilizes many features from Cocos2d-html5 engine, including: Parallax background, tilemap, actions, ease, frame animation, schedule, Labels, keyboard Dispatcher, Scene Transition. \n    Art and audio is copyrighted by Enigmata Genus Revenge, you may not use any copyrigted material without permission. This showcase is licensed under GPL. \n \n Programmer: \n Shengxiang Chen (陈升想) \n Dingping Lv (吕定平) \n Effects animation: Hao Wu(吴昊)\n Quality Assurance:  Sean Lin(林顺)", "Arial", 14, CCSize(size.width * 0.85, 320), kCCTextAlignmentLeft);
	pLabel->setPosition( ccp(size.width / 2, size.height / 2 - 20) );
    pLabel->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(pLabel, 1);
    
    // goback label
    CCLabelTTF *pGoBack = CCLabelTTF::create("Go Back", "Arial", 14);
    CCMenuItemLabel *pGoBackMenu = CCMenuItemLabel::create(pGoBack, this, menu_selector(AboutLayer::gobackCallback));
    CCMenu *pMenu = CCMenu::create(pGoBackMenu, NULL);
    pMenu->setPosition(ccp(size.width / 2, 40));
    this->addChild(pMenu);
    
    return true;
}

void AboutLayer::gobackCallback(CCObject *pSender)
{
    CCScene *pScene = CCScene::create();
    pScene->addChild(HelloWorld::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pScene));
}

