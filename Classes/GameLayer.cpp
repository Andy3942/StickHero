//
//  GameLayer.cpp
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#include "GameLayer.h"

GameLayer::GameLayer()
:_stake_x(0)
{
}

GameLayer::~GameLayer()
{
}

GameLayer* GameLayer::create(Color4B color)
{
    auto ret = new GameLayer();
    ret->autorelease();
    ret->initWithColor(color);
    return ret;
}

void GameLayer::star()
{
    addStakes();
    loadHero();
    addTouchEventListener();
}

void GameLayer::addStakes()
{
    while (_stake_x < Director::getInstance()->getWinSize().width)
    {
        addStake();
    }
}

void GameLayer::addStake()
{
    int width = random(80, 200);
    auto stake_sprite = StakeSprite::create(width, 300);
    addChild(stake_sprite);
    _stake_sprite.pushBack(stake_sprite);
    int x = _stake_x;
    if(x != 0)
    {
        int distance = random(20, 400);
        x += distance;
        stake_sprite->setPositionX(x);
    }
    _stake_x = x + width;
}

void GameLayer::loadHero()
{
    _hero_sprite = HeroSprite::create();
    addChild(_hero_sprite);
    _hero_sprite->setPosition(0, 300);
}

void GameLayer::stickCollapseEndCall(Node* node)
{
    int hero_x = _hero_sprite->getPositionX();
    int stick_x = _stick_sprite->getPositionX();
    int distance = stick_x - hero_x + _stick_sprite->getContentSize().height;
    _hero_sprite->run(distance, CallFuncN::create(CC_CALLBACK_1(GameLayer::heroRunEndCall, this)));
}

void GameLayer::heroRunEndCall(Node* node)
{

}

void GameLayer::addTouchEventListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    int count = _stake_sprite.size();
    for (int i = 0; i < count; ++i)
    {
        auto stake_sprite = _stake_sprite.at(i);
        if (_hero_sprite->getPositionX() >= stake_sprite->getPositionX() && _hero_sprite->getPositionX() <= stake_sprite->getPositionX() + stake_sprite->getContentSize().width)
        {
            auto stick_sprite = StickSprite::create();
            addChild(stick_sprite);
            stick_sprite->setAnchorPoint(Vec2(1, 0));
            stick_sprite->setPosition(stake_sprite->getPositionX() + stake_sprite->getContentSize().width, stake_sprite->getContentSize().height);
            stick_sprite->grow();
            _stick_sprite = stick_sprite;
            break;
        }
    }
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    _stick_sprite->stopGrow();
    _stick_sprite->collapse(CallFuncN::create(CC_CALLBACK_1(GameLayer::stickCollapseEndCall, this)));
}

void GameLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    onTouchEnded(touch, unused_event);
}