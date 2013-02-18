//
//  SettingsScene.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-11.
//
//

#include "SettingsScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "ResourcePath.h"
#include "CCSprite.h"
#include "HelloWorldScene.h"
#include "GameConfig.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SettingsLayer::scene()
{
    CCScene *scene = CCScene::create();
    SettingsLayer *layer = SettingsLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SettingsLayer::init()
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
    
    // option title
    CCTexture2D *pMenuTitleTex = CCTextureCache::sharedTextureCache()->addImage(s_menuTile);
    CCSprite *pTitle = CCSprite::createWithTexture(pMenuTitleTex, CCRectMake(0, 0, 134, 34));
    pTitle->setPosition(ccp(size.width / 2, size.height - 120));
    this->addChild(pTitle);

    // MenuItem
    // -Sound
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont *pSoundMenu = CCMenuItemFont::create("Sound");
    pSoundMenu->setEnabled(false);
    
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(26);
    CCMenuItemToggle *pSoundItem = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingsLayer::soundControlCallback),CCMenuItemFont::create("On"), CCMenuItemFont::create("Off"), NULL);
    pSoundItem->setSelectedIndex(MW_SOUND ? 0 : 1);
    
    // -Mode
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont *pModeMenu = CCMenuItemFont::create("Mode");
    pModeMenu->setEnabled(false);
    
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(26);
    CCMenuItemToggle *pModeItem = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingsLayer::modeControlCallback), CCMenuItemFont::create("Easy"), CCMenuItemFont::create("Normal"), CCMenuItemFont::create("Hard"), NULL);
    
    // go back
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(26);
    CCLabelTTF *pGoBackLabel = CCLabelTTF::create("Go Back", "Arial", 20);
    CCMenuItemLabel *pGoBackMenuLable = CCMenuItemLabel::create(pGoBackLabel, this, menu_selector(SettingsLayer::gobackCallback));
    pGoBackMenuLable->setScale(0.8);
    
    // Menu
    CCMenu *pMenu = CCMenu::create(pSoundMenu, pModeMenu, pSoundItem, pModeItem, pGoBackMenuLable, NULL);
    pMenu->alignItemsInColumns(2, 2, 1);
    this->addChild(pMenu);
    
    pGoBackMenuLable->setPositionY(pGoBackMenuLable->getPositionY() - 50);
    
    return true;
}

void SettingsLayer::soundControlCallback(CCObject*)
{
    MW_SOUND = !MW_SOUND;
    if(!MW_SOUND)
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void SettingsLayer::gobackCallback(CCObject*)
{
    CCScene *pScene = CCScene::create();
    pScene->addChild(HelloWorld::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pScene));
}

void SettingsLayer::modeControlCallback(CCObject*)
{
    
}