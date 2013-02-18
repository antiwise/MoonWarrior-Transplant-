//
//  LevelManager.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#ifndef __HelloMoonWarriors__LevelManager__
#define __HelloMoonWarriors__LevelManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameLayer;

class LevelManager {
private:
    GameLayer *gameLayer;
    void addEnemyToGameLayer(int);
    
public:
    LevelManager(GameLayer*);
    void loadLevelResource(int);
};

#endif /* defined(__HelloMoonWarriors__LevelManager__) */
