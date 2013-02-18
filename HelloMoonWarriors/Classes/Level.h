//
//  Level.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-16.
//
//

#ifndef __HelloMoonWarriors__Level__
#define __HelloMoonWarriors__Level__

#include <iostream>

struct enemyMetadata {
    const char* ShowType;
    int ShowTime;
    int Types[3];
    int TypeNum;
};

class LevelConst {
    
private:
    LevelConst();
    virtual ~LevelConst();
    static LevelConst *_instance;
    
public:
    static LevelConst* GetInstance();
    enemyMetadata enemies[2];
    const int enemyNum;
};

#endif /* defined(__HelloMoonWarriors__Level__) */
