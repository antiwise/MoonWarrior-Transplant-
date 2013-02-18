//
//  GameControlMenu.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__GameControlMenu__
#define __HelloMoonWarriors__GameControlMenu__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameControlMenuLayer : public cocos2d::CCLayer
{
private:
    
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // callback
    void menuCallback(CCObject*);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameControlMenuLayer);
};

#endif /* defined(__HelloMoonWarriors__GameControlMenu__) */
