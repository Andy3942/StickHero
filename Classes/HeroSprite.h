//
//  HeroSprite.h
//  StickHero
//
//  Created by bzx-mac on 7/9/15.
//
//

#ifndef __StickHero__HeroSprite__
#define __StickHero__HeroSprite__

#include <stdio.h>

USING_NS_CC;

class HeroSprite:public Sprite
{
public:
    static HeroSprite* create();

    void run();

    void stop();

    void fall();

    void loadBody();
private:
    Sprite* _body;
};
#endif /* defined(__StickHero__HeroSprite__) */
