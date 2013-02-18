#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCSprite.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:
    CCSprite *ship;
    void onButtonEffect();
    void newGameEffectCallback();
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // menu callback
    void menuNewGameCallback(CCObject* pSender);
    void menuGameSettingsCallback(CCObject* pSender);
    void menuAboutCallback(CCObject* pSender);
    
    // update scheduler
    void updateLoading(float);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
