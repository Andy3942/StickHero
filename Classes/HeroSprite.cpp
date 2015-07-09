//
//  HeroSprite.cpp
//  StickHero
//
//  Created by bzx-mac on 7/9/15.
//
//

#include "HeroSprite.h"

HeroSprite* HeroSprite::create()
{
    auto ret = new HeroSprite();
    ret->autorelease();
    ret->init();
    ret->loadBody();
    return ret;
}

void HeroSprite::loadBody()
{
    _body = Sprite::create();
    addChild(_body);
    auto temp = LayerColor::create(Color4B(255, 0, 0, 255), 10, 20);
    _body->addChild(temp);
}

void HeroSprite::run()
{
}

void HeroSprite::stop()
{
}

void HeroSprite::fall()
{

}