
//
//  LevelManager.cpp
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#include "LevelManager.h"
#include "Level.h"
#include "Enemy.h"
#include "EnemyType.h"
#include "GameScene.h"
#include "GameConfig.h"

using namespace cocos2d;

LevelManager::LevelManager(GameLayer* layer)
{
    this->gameLayer = layer;
}

void LevelManager::loadLevelResource(int deltaTime)
{
    //load enemies
    for (int i = 0; i < LevelConst::GetInstance()->enemyNum; i++) {
        enemyMetadata enemy = LevelConst::GetInstance()->enemies[i];
        if (!strcmp(enemy.ShowType, "Once") && enemy.ShowTime == deltaTime) {
            for (int j = 0; j < enemy.TypeNum; j++) {
                this->addEnemyToGameLayer(enemy.Types[j]);
            }
        }
        else if (!strcmp(enemy.ShowType, "Repeate") && deltaTime % enemy.ShowTime == 0)
        {
            for (int j = 0; j < enemy.TypeNum; j++) {
                this->addEnemyToGameLayer(enemy.Types[j]);
            }
        }
    }
}

void LevelManager::addEnemyToGameLayer(int typeIdx)
{
    Enemy *addEnemy = new Enemy(EnemyTypeMgr::GetInstance()->enemyTypes[typeIdx]);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint enemyPos = ccp(size.width - 160 * rand() / double(RAND_MAX), size.height);
    //CCPoint enemyPos = ccp(80 + (size.width - 160 * rand() / double(RAND_MAX)), size.height);
    CCSize enemyCs = addEnemy->getContentSize();
    addEnemy->setPosition(enemyPos);
    
    
    CCPoint offset;
    CCAction *tmpAction;
    CCMoveBy *a0, *a1;
    
    switch (addEnemy->moveType) {
        case ATTACK:
        {
            offset = this->gameLayer->ship->getPosition();
            tmpAction = CCMoveTo::create(1, offset);
        }
        break;
            
        case VERTICAL:
        {
            offset = ccp(0, -size.height - enemyCs.height);
            tmpAction = CCMoveBy::create(4, offset);
        }
        break;
            
        case HORIZONTAL:
        {
            offset = ccp(0, -100 - 200 * rand() / double(RAND_MAX));
            a0 = CCMoveBy::create(0.5, offset);
            a1 = CCMoveBy::create(1, ccp(-50 - 100 * rand() / double(RAND_MAX), 0));
            CCCallFunc *onComplete = CCCallFunc::create(addEnemy, callfunc_selector(Enemy::actionComplete));
            tmpAction = CCSequence::create(a0, a1, onComplete, NULL);
        }
        break;
            
        case OVERLAP:
        {
            int newX = enemyPos.x <= size.width / 2 ? 320 : -320;
            a0 = CCMoveBy::create(4, ccp(newX, -240));
            a1 = CCMoveBy::create(4, ccp(newX, -320));
            offset = ccp(0, -size.height - enemyCs.height);
            tmpAction = CCSequence::create(a0, a1, NULL);
        }
        break;
    }
    
    this->gameLayer->addChild(addEnemy, addEnemy->zOrder, ENEMY);
    GameConfig::GetInstance()->MW_CONTAINER_ENEMY->addObject(addEnemy);
    addEnemy->runAction(tmpAction);
}