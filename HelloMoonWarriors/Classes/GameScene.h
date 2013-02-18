//
//  GameScene.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__GameScene__
#define __HelloMoonWarriors__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Ship.h"
#include "LevelManager.h"

using namespace cocos2d;

class Bullet;
class Enemy;

class GameLayer : public cocos2d::CCLayer
{
private:
    //bg
    CCSprite *backSky;
    float backSkyHeight;
    CCTMXTiledMap *backTileMap;
    float backTileMapHeight;
    //tilemap
    bool isBackSkyReload;
    bool isBackTileReload;
    CCSprite *backSkyRe;
    CCTMXTiledMap *backTileMapRe;
    
    CCRect screenRect;
    CCLabelTTF *lbScore;
    CCTexture2D *shipTexture;
    CCSprite *life;
    CCLabelTTF *lbLife;
    bool isTouch;
    
    //score
    int tmpScore;
    char* scoreLabelStr;
    //life
    char* lifeLabelStr;
    
    //levelmgr
    LevelManager *levelMgr;
    int time;
    
    void initBackground();
    void movingBackground(float);
    
    void update(float);
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void processEvent(CCTouch*);
    void removeInactiveUnit(float dt);
    void checkIsCollide();
    void updateUI();
    void checkIsReborn();
    void scoreCounter();
    
    void onGameOver();
    
    bool collide(Bullet*, Enemy*);
    bool collide(Ship*, Enemy*);
    bool collide(Ship*, Bullet*);
    
public:
    Ship *ship;
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    
    virtual ~GameLayer();
};

#endif /* defined(__HelloMoonWarriors__GameScene__) */
