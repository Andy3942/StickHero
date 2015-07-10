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

enum class GameStatus
{
    STAND,
    MOVE,
    OVER,
};

class GameLayer:public LayerColor
{
public:
    GameLayer();
    virtual ~GameLayer();

    static GameLayer* create(Color4B color);
    
    void initData();
    void start();
    void restart();
    void gameOver();
    void restartCallback(Ref* sender);
    void addStake();
    void addStakes();
    void loadHero();
    void refreshScore(bool is_need_create = false);
    void addTouchEventListener();
    void stickCollapseEndCall(Node* node);
    void heroRunEndCall(Node* node);
    void move();
    void moveCall(Node* node);
    void moveEnd();
    void setScore(int score);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:
    HeroSprite* _hero_sprite;
    Vector<StakeSprite*> _stake_sprites;
    Vector<StickSprite*> _stick_sprites;
    StickSprite* _cur_stick_sprite;
    int _stake_x;
    int _stake_max_x;
    int _cur_stake_index;
    Action* _move_action;
    int _move_distance;
    GameStatus _game_status;
    Label* _score_label;
    int _score;
};

#endif /* defined(__StickHero__GameLayer__) */
