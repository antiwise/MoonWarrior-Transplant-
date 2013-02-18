//
//  GameoverScene.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#ifndef __HelloMoonWarriors__GameoverScene__
#define __HelloMoonWarriors__GameoverScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameoverLayer : public CCLayer {
private:
    char* finalScoreLabel;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual ~GameoverLayer();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    //callback
    void playAgainCallback();
    void onPlayAgain();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameoverLayer);
};

#endif /* defined(__HelloMoonWarriors__GameoverScene__) */
