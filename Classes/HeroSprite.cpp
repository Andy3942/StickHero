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

void HeroSprite::initData()
{
    _hero_status = HeroStatus::STAND;
}

void HeroSprite::loadBody()
{
    _body = Sprite::create("res/hero/run/7.png");
    addChild(_body);
    _body->setPositionY(5);
//    auto temp = LayerColor::create(Color4B(255, 0, 0, 255), 10, 20);
//    _body->addChild(temp);
}

void HeroSprite::run(int distance, CallFuncN* run_end_call)
{
    float time = distance / 100;
    auto move_by = MoveBy::create(time, Vec2(distance, 0));
    auto stop_call = CallFunc::create(CC_CALLBACK_0(HeroSprite::stop, this));
    auto run_action = Sequence::create(move_by, stop_call, run_end_call, NULL);
    runAction(run_action);
    Vector<SpriteFrame*> sfs;
    for(int i = 1; i <= 16; ++i)
    {
        std::string filename = StringUtils::format("res/hero/run/%d.png", i);
        auto sf = SpriteFrame::create(filename, Rect(0, 0, 120, 129));
        sfs.pushBack(sf);
    }
    auto animation = Animation::createWithSpriteFrames(sfs, 0.15f);
    _run_action = RepeatForever::create(Animate::create(animation));
    _body->runAction(_run_action);
}

void HeroSprite::stop()
{
    _body->stopAction(_run_action);
}

void HeroSprite::fall()
{
    auto move_by = MoveBy::create(1, Vec2(0, -500));
    runAction(move_by);
}

void HeroSprite::setStatus(HeroStatus status)
{
    _hero_status = status;
}