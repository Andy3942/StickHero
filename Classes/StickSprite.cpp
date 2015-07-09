//
//  StickSprite.cpp
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#include "StickSprite.h"

StickSprite* StickSprite::create()
{
    auto ret = new StickSprite();
    ret->init();
    ret->autorelease();
    ret->loadBody();
    return ret;
}

void StickSprite::loadBody()
{
    _body = LayerColor::create(Color4B(0, 0, 0, 255), 5, 0);
    addChild(_body);
    setContentSize(_body->getContentSize());
}

void StickSprite::grow()
{
    auto delay_time = DelayTime::create(0.03);
    auto add_height_callfun = CallFuncN::create(CC_CALLBACK_1(StickSprite::addHeight, this));
    auto grow_sequence = Sequence::create(delay_time, add_height_callfun, NULL);
    _grow_action = RepeatForever::create(grow_sequence);
    runAction(_grow_action);
}

void StickSprite::stopGrow()
{
    stopAction(_grow_action);
}

void StickSprite::addHeight(Node* node)
{
    auto size = _body->getContentSize();
    size.height += 13;
    _body->setContentSize(size);
    setContentSize(_body->getContentSize());
}

void StickSprite::collapse(CallFuncN* end_call_fun)
{
    auto rotate_to = RotateTo::create(0.5, 90);
    auto collapse_action = Sequence::create(rotate_to, end_call_fun, NULL);
    runAction(collapse_action);
}