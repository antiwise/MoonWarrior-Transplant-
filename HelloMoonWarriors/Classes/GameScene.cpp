//
//  GameScene.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "ResourcePath.h"
#include "CCSprite.h"
#include "HelloWorldScene.h"
#include "GameConfig.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameoverScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

GameLayer::~GameLayer()
{
    if (ship != NULL) {
        delete ship;
        ship = NULL;
    }
    if (scoreLabelStr != NULL) {
        delete[] scoreLabelStr;
        scoreLabelStr = NULL;
    }if (levelMgr != NULL) {
        delete levelMgr;
    }
    if (lifeLabelStr != NULL) {
        delete[] lifeLabelStr;
    }
    GameConfig::GetInstance()->ResetArray();
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // init vars
    MW_LIFE = 4;
    MW_SCORE = 0;
    gameStatus = STATE_PLAYING;

    isBackSkyReload = false;
    isBackTileReload = false;
    
    isTouch = false;
    
    tmpScore = 0;
    scoreLabelStr = new char[30];
    lifeLabelStr = new char[10];
    
    time = 0;
    // init done!
    
    Enemy::sharedEnemy();
    levelMgr = new LevelManager(this);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    initBackground();
    this->screenRect = CCRectMake(0, 0, size.width, size.height + 10);
    
    //score
    this->lbScore = CCLabelTTF::create("Score: 0", "Arial", 14, CCSizeMake(80,14), kCCTextAlignmentRight);
    this->lbScore->setAnchorPoint(ccp(1,0));
    this->addChild(this->lbScore, 1000);
    this->lbScore->setPosition(ccp(size.width - 5, size.height - 20));
    
    //ship life
    this->shipTexture = CCTextureCache::sharedTextureCache()->addImage(s_ship01);
    this->life = CCSprite::createWithTexture(this->shipTexture, CCRectMake(0, 0, 60, 38));
    this->life->setScale(0.6);
    this->life->setPosition(ccp(30, 460));
    this->addChild(this->life, 1, 5);
    
    //ship life count
    this->lbLife = CCLabelTTF::create("0", "Arial", 20);
    this->lbLife->setPosition(ccp(69, 463));
    this->lbLife->setColor(ccRED);
    this->addChild(this->lbLife, 1000);
    
    //ship
    this->ship = new Ship();
    this->addChild(this->ship, this->ship->zOrder, PLAYER);
    
    //accept touch now!
    this->setTouchEnabled(true);
    
    //schedule
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameLayer::scoreCounter), 1);
    
    if (MW_SOUND) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_bgMusic, true);
    }
    
    return true;
}

void GameLayer::scoreCounter()
{
    if (gameStatus == STATE_PLAYING) {
        this->time++;
        this->levelMgr->loadLevelResource(this->time);
    }
}

void GameLayer::update(float dt)
{
    if (gameStatus == STATE_PLAYING) {
        removeInactiveUnit(dt);
        checkIsCollide();
        checkIsReborn();
        updateUI();
    }
}

void GameLayer::removeInactiveUnit(float dt)
{
    CCArray *children = this->getChildren();
    for (int i = 0; i < children->count(); i++) {
        Ship *shipChild = dynamic_cast<Ship*>(children->objectAtIndex(i));
        if (shipChild != NULL) {
            shipChild->update(dt);
            int tag = shipChild->getTag();
            if (tag == PLAYER || tag == PLAYER_BULLET || tag == ENEMY || tag == ENEMEY_BULLET) {
                if (shipChild && !shipChild->active) {
                    shipChild->destroy();
                    cout << "destroy one ship!" << endl;
                }
            }
            continue;
        }
        Bullet *bulletChild = dynamic_cast<Bullet*>(children->objectAtIndex(i));
        if (bulletChild != NULL) {
            bulletChild->update(dt);
            int tag = bulletChild->getTag();
            if (tag == PLAYER || tag == PLAYER_BULLET || tag == ENEMY || tag == ENEMEY_BULLET) {
                if (bulletChild && !bulletChild->active) {
                    bulletChild->destroy();
                    cout << "destroy one bullet!" << endl;
                }
            }
            continue;
        }
        Enemy *enemyChild = dynamic_cast<Enemy*>(children->objectAtIndex(i));
        if (enemyChild != NULL) {
            enemyChild->update(dt);
            int tag = enemyChild->getTag();
            if (tag == PLAYER || tag == PLAYER_BULLET || tag == ENEMY || tag == ENEMEY_BULLET) {
                if (enemyChild && !enemyChild->active) {
                    enemyChild->destroy();
                    cout << "destroy one enemy!" << endl;
                }
            }
            continue;
        }
        cout << "nothing to destroy!" << endl;
    }
    cout << children->count() << endl;
}

void GameLayer::checkIsCollide()
{
    for (int k = 0; k < GameConfig::GetInstance()->MW_CONTAINER_ENEMY->count(); k++) {
        Enemy *enemyChild = dynamic_cast<Enemy*>(GameConfig::GetInstance()->MW_CONTAINER_ENEMY->objectAtIndex(k));
        //loop all player's bullets
        for (int i = 0; i < GameConfig::GetInstance()->MW_CONTAINER_PLAYER_BULLETS->count(); i++) {
            Bullet *bulletChild = dynamic_cast<Bullet*>(GameConfig::GetInstance()->MW_CONTAINER_PLAYER_BULLETS->objectAtIndex(i));
            
            // bullet hits enemy
            if (this->collide(bulletChild, enemyChild)) {
                bulletChild->hurt();
                enemyChild->hurt();
            }
            
            // bullet is out of screen
            if (!this->screenRect.intersectsRect(bulletChild->boundingBox())) {
                bulletChild->destroy();
            }
        }
        
        // enemy hits player
        if (this->collide(this->ship, enemyChild)) {
            if (this->ship->active) {
                enemyChild->hurt();
                this->ship->hurt();
            }
        }

        // enemy is out of screen
        if (!this->screenRect.intersectsRect(enemyChild->boundingBox())) {
            enemyChild->destroy();
        }
        
    }
    
    for (int i = 0; i < GameConfig::GetInstance()->MW_CONTAINER_ENEMY_BULLETS->count(); i++) {
        Bullet *bulletChild = dynamic_cast<Bullet*>(GameConfig::GetInstance()->MW_CONTAINER_ENEMY_BULLETS->objectAtIndex(i));
        if (this->collide(this->ship, bulletChild)) {
            if (this->ship->active) {
                this->ship->hurt();
                bulletChild->hurt();
            }
        }
        if (!this->screenRect.intersectsRect(bulletChild->boundingBox())) {
            bulletChild->destroy();
        }
    }
}

void GameLayer::updateUI()
{
    if (this->tmpScore < MW_SCORE) {
        this->tmpScore += 5;
    }
    
    sprintf(lifeLabelStr, "%d", MW_LIFE);
    this->lbLife->setString(this->lifeLabelStr);
    
    sprintf(this->scoreLabelStr, "Score: %d", this->tmpScore);
    this->lbScore->setString(this->scoreLabelStr);
}

void GameLayer::checkIsReborn()
{
    if (MW_LIFE > 0 && !this->ship->active) {
        //ship
        this->ship = new Ship();
        this->addChild(this->ship, this->ship->zOrder, PLAYER);
    }
    else if (MW_LIFE <= 0 && !this->ship->active)
    {
        gameStatus = STATE_GAMEOVER;
        this->ship = NULL;
        this->runAction(CCSequence::create(CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(GameLayer::onGameOver)), NULL));
    }
}

void GameLayer::onGameOver()
{
    CCScene *scene = CCScene::create();
    scene->addChild(GameoverLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    this->isTouch = true;
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (this->isTouch) {
        processEvent((CCTouch*)(pTouches->anyObject()));
    }
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    this->isTouch = false;
}

void GameLayer::processEvent(CCTouch* touch)
{
    if (gameStatus == STATE_PLAYING) {
        CCPoint delta = touch->getDelta();
        CCPoint curPos = this->ship->getPosition();
        curPos = ccpAdd(curPos, delta);
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        curPos = ccpClamp(curPos, CCPointZero, ccp(size.width, size.height));
        this->ship->setPosition(curPos);
    }
}

bool GameLayer::collide(Bullet* bullet, Enemy* enemy)
{
    CCRect a = bullet->collideRect();
    CCRect b = enemy->collideRect();
    if (a.intersectsRect(b)) {
        return true;
    }
    else {
        return false;
    }
}

bool GameLayer::collide(Ship* ship, Enemy* enemy)
{
    CCRect a = ship->collideRect();
    CCRect b = enemy->collideRect();
    if (a.intersectsRect(b)) {
        return true;
    }
    else {
        return false;
    }
}

bool GameLayer::collide(Ship* ship, Bullet* bullet)
{
    CCRect a = ship->collideRect();
    CCRect b = bullet->collideRect();
    if (a.intersectsRect(b)) {
        return true;
    }
    else {
        return false;
    }
}

void GameLayer::initBackground()
{
    //bg
    this->backSky = CCSprite::create(s_bg01);
    this->backSky->setAnchorPoint(ccp(0, 0));
    this->backSkyHeight = backSky->getContentSize().height;
    this->addChild(backSky, -10);
    
    //tilemap
    this->backTileMap = CCTMXTiledMap::create(s_level01);
    this->addChild(backTileMap, -9);
    this->backTileMapHeight = this->backTileMap->getMapSize().height * this->backTileMap->getTileSize().height;
    
    this->backSkyHeight -= 48;
    this->backTileMapHeight -= 200;
    this->backSky->runAction(CCMoveBy::create(3, ccp(0, -48)));
    this->backTileMap->runAction(CCMoveBy::create(3, ccp(0, -200)));
    
    this->schedule(schedule_selector(GameLayer::movingBackground), 3);
}

void GameLayer::movingBackground(float)
{
    this->backSky->runAction(CCMoveBy::create(3, ccp(0, -48)));
    this->backTileMap->runAction(CCMoveBy::create(3, ccp(0, -200)));
    this->backSkyHeight -= 48;
    this->backTileMapHeight -= 200;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    if (this->backSkyHeight <= size.height) {
        if(!this->isBackSkyReload)
        {
            this->backSkyRe = CCSprite::create(s_bg01);
            this->backSkyRe->setAnchorPoint(ccp(0,0));
            this->addChild(backSkyRe, -10);
            this->backSkyRe->setPosition(ccp(0, size.height));
            this->isBackSkyReload = true;
        }
        this->backSkyRe->runAction(CCMoveBy::create(3, ccp(0, -48)));
    }
    
    if (this->backSkyHeight <= 0) {
        this->backSkyHeight = this->backSky->getContentSize().height;
        this->removeChild(backSky, true);
        this->backSky = this->backSkyRe;
        this->backSkyRe = NULL;
        this->isBackSkyReload = false;
    }
    
    if (this->backTileMapHeight <= size.height) {
        if(!this->isBackTileReload)
        {
            this->backTileMapRe = CCTMXTiledMap::create(s_level01);
            this->addChild(backTileMapRe, -9);
            this->backTileMapRe->setPosition(ccp(0, size.height));
            this->isBackTileReload = true;
        }
        this->backTileMapRe->runAction(CCMoveBy::create(3, ccp(0, -200)));
    }
    
    if (this->backTileMapHeight <= 0) {
        this->backTileMapHeight = this->backTileMapRe->getMapSize().height * this->backTileMapRe->getTileSize().height;
        this->removeChild(backTileMap, true);
        this->backTileMap = this->backTileMapRe;
        this->backTileMapRe = NULL;
        this->isBackTileReload = false;
    }
                             
}