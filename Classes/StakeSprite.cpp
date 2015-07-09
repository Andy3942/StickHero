//
//  StakeSprite.cpp
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#include "StakeSprite.h"

StakeSprite* StakeSprite::create(int width, int height)
{
    auto ret = new StakeSprite();
    ret->init();
    ret->autorelease();
    auto body = LayerColor::create(Color4B(0, 0, 0, 255), width, height);
    ret->addChild(body);
    ret->setContentSize(body->getContentSize());
    ret->setAnchorPoint(Vec2(0, 0));
    return ret;
}