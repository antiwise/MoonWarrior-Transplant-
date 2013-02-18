//
//  FlareEffect.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-12.
//
//

#ifndef __HelloMoonWarriors__FlareEffect__
#define __HelloMoonWarriors__FlareEffect__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef void (*CCNodeFunc)(CCNode*);

void flareEffect(CCNode *parent, SEL_CallFunc callback);
void killFlareCallback(CCNode*);

void spark(CCPoint, CCNode*, float scale, float duration);

#endif /* defined(__HelloMoonWarriors__FlareEffect__) */
