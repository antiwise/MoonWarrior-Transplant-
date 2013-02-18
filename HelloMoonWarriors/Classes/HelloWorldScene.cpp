#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCSprite.h"
#include "CCMenuItem.h"
#include "ResourcePath.h"
#include <CoreGraphics/CGGeometry.h>
#include "Constants.h"
#include <cstdlib>
#include "AboutScene.h"
#include "SettingsScene.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "GameControlMenu.h"
#include "FlareEffect.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // set background
    CCSprite *pBackGround = CCSprite::create(s_loading);
    pBackGround->setAnchorPoint(CCPointZero);
    this->addChild(pBackGround, 0, loadingTag);
    
    // logo
    CCSprite *pLogo = CCSprite::create(s_logo);
    pLogo->setAnchorPoint(CCPointZero);
    pLogo->setPosition(ccp(0, 250));
    this->addChild(pLogo, 10, logoTag);

    // menu
    CCSprite *pNewGameNormalSprite = CCSprite::create(s_menu, CCRectMake(0, 0, 126, 33));
    CCSprite *pNewGameSelectedSprite = CCSprite::create(s_menu, CCRectMake(0, 33, 126, 33));
    CCSprite *pNewGameDisabledSprite = CCSprite::create(s_menu, CCRectMake(0, 33 * 2, 126, 33));
    
    CCSprite *pGameSettingsNormalSprite = CCSprite::create(s_menu, CCRectMake(126, 0, 126, 33));
    CCSprite *pGameSettingsSelectedSprite = CCSprite::create(s_menu, CCRectMake(126, 33, 126, 33));
    CCSprite *pGameSettingsDisabledSprite = CCSprite::create(s_menu, CCRectMake(126, 33 * 2, 126, 33));
    
    CCSprite *pAboutNormalSprite = CCSprite::create(s_menu, CCRectMake(252, 0, 126, 33));
    CCSprite *pAboutSelectedSprite = CCSprite::create(s_menu, CCRectMake(252, 33, 126, 33));
    CCSprite *pAboutDisabledSprite = CCSprite::create(s_menu, CCRectMake(252, 33 * 2, 126, 33));
    
    CCMenuItemSprite *pNewGameSprite = CCMenuItemSprite::create(pNewGameNormalSprite, pNewGameSelectedSprite, pNewGameDisabledSprite, this, menu_selector(HelloWorld::menuNewGameCallback));
    CCMenuItemSprite *pGameSettingsSprite = CCMenuItemSprite::create(pGameSettingsNormalSprite, pGameSettingsSelectedSprite, pGameSettingsDisabledSprite, this, menu_selector(HelloWorld::menuGameSettingsCallback));
    CCMenuItemSprite *pAboutSprite = CCMenuItemSprite::create(pAboutNormalSprite, pAboutSelectedSprite, pAboutDisabledSprite, this, menu_selector(HelloWorld::menuAboutCallback));
    
    CCMenu *pMenu = CCMenu::create(pNewGameSprite, pGameSettingsSprite, pAboutSprite, NULL);
    pMenu->alignItemsVerticallyWithPadding(10);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition(ccp(size.width/2, size.height/2 - 80));
    this->addChild(pMenu, 1, menuTag);
    
    // create ship sprite
    CCTexture2D *pShipTex = CCTextureCache::sharedTextureCache()->addImage(s_ship01);
    this->ship = CCSprite::createWithTexture(pShipTex, CCRectMake(0, 45, 60, 38));
    this->addChild(this->ship, 0, ship01Tag);
    
    // schedule
    this->schedule(schedule_selector(HelloWorld::updateLoading), 0.1);

    CCPoint startPoint = ccp(rand() / double(RAND_MAX) * size.width, 0);
    this->ship->setPosition(startPoint);
    this->ship->runAction(CCMoveBy::create(2, ccp(rand() / double(RAND_MAX) * size.width, startPoint.y + size.height + 100)));

    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_mainMainMusic, true);
    }
    
    return true;
}

void HelloWorld::newGameEffectCallback()
{
    CCScene *pScene = CCScene::create();
    pScene->addChild(GameLayer::create());
    pScene->addChild(GameControlMenuLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pScene));
}

void HelloWorld::menuNewGameCallback(CCObject* pSender)
{
    this->onButtonEffect();
    // flare effect
    flareEffect(this, callfunc_selector(HelloWorld::newGameEffectCallback));
}

void HelloWorld::menuGameSettingsCallback(CCObject* pSender)
{
    this->onButtonEffect();
    CCScene *pSettingsScene = CCScene::create();
    pSettingsScene->addChild(SettingsLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pSettingsScene));
}

void HelloWorld::menuAboutCallback(CCObject* pSender)
{
    this->onButtonEffect();
    CCScene *pAboutScene = CCScene::create();
    pAboutScene->addChild(AboutLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, pAboutScene));
}

void HelloWorld::updateLoading(float)
{
    if (this->ship->getPosition().y > 480) {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCPoint startPoint = ccp(rand() / double(RAND_MAX) * size.width, 0);
        this->ship->setPosition(startPoint);
        this->ship->runAction(CCMoveBy::create(2, ccp(rand() / double(RAND_MAX) * size.width, startPoint.y + 480)));
    }
}

void HelloWorld::onButtonEffect()
{
    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->playEffect(s_buttonEffect);
    }
}
