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

enum class HeroStatus
{
    STAND,
    RUN,
    FALL
};
    
class HeroSprite:public Sprite
{
public:
    static HeroSprite* create();
    
    void initData();
    void run(int distance, CallFuncN* run_end_call);
    void stop();
    void fall();
    void loadBody();
    void setStatus(HeroStatus status);
private:
    Sprite* _body;
    HeroStatus _hero_status;
    Action* _run_action;
};
#endif /* defined(__StickHero__HeroSprite__) */
