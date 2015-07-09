//
//  GameLayer.h
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#ifndef __StickHero__GameLayer__
#define __StickHero__GameLayer__

#include <stdio.h>

#include "StakeSprite.h"
#include "HeroSprite.h"
#include "StickSprite.h"

USING_NS_CC;

class GameLayer:public LayerColor
{
public:
    GameLayer();
    virtual ~GameLayer();

    static GameLayer* create(Color4B color);

    void star();
    void addStake();
    void addStakes();
    void loadHero();
    void addTouchEventListener();
    void stickCollapseEndCall(Node* node);
    void heroRunEndCall(Node* node);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:
    HeroSprite* _hero_sprite;
    Vector<StakeSprite*> _stake_sprite;
    StickSprite* _stick_sprite;
    int _stake_x;
};

#endif /* defined(__StickHero__GameLayer__) */
