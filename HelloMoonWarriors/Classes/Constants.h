//
//  Constants.h
//  HelloMoonWarriors
//
//  Created by Benjamin Tang on 13-2-11.
//
//

#ifndef HelloMoonWarriors_Constants_h
#define HelloMoonWarriors_Constants_h

extern const int loadingTag;
extern const int logoTag;
extern const int menuTag;
extern const int ship01Tag;

enum GameStatus
{
    STATE_PLAYING = 0,
    STATE_GAMEOVER,
};

extern GameStatus gameStatus;

#endif
