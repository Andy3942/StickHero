//
//  GameLayer.cpp
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#include "GameLayer.h"

static const int STAKE_HEIGHT = 300;

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::initData()
{
    _game_status = GameStatus::STAND;
    _move_distance = 0;
    _stake_sprites.clear();
    _stick_sprites.clear();
    _stake_x = 0;
    _stake_max_x = Director::getInstance()->getWinSize().width;
    _cur_stake_index = 0;
    _move_distance = 0;
    _score = 0;
}

GameLayer* GameLayer::create(Color4B color)
{
    auto ret = new GameLayer();
    ret->autorelease();
    ret->initWithColor(color);
    ret->initData();
    ret->addTouchEventListener();
    return ret;
}

void GameLayer::start()
{
    addStakes();
    loadHero();
    refreshScore(true);
}

void GameLayer::restart()
{
    removeAllChildren();
    initData();
    start();
}

void GameLayer::restartCallback(Ref* sender)
{
    restart();
}

void GameLayer::gameOver()
{
    _game_status = GameStatus::OVER;
    auto menu = Menu::create();
    addChild(menu);
    menu->setPosition(0, 0);
    auto restartBtn = MenuItemFont::create("restart", CC_CALLBACK_1(GameLayer::restartCallback, this));
    menu->addChild(restartBtn);
    restartBtn:setAnchorPoint(Vec2(0, 1));
    restartBtn->setPosition(getContentSize().width * 0.5, getContentSize().height * 0.5);
}

void GameLayer::addStakes()
{   
    while (_stake_x < _stake_max_x)
    {
        addStake();
    }
}

void GameLayer::addStake()
{
    int width = random(80, 200);
    auto stake_sprite = StakeSprite::create(width, STAKE_HEIGHT);
    addChild(stake_sprite);
    _stake_sprites.pushBack(stake_sprite);
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
    auto i = _stake_sprites.begin();
    auto stake_sprite = *i;
    _hero_sprite = HeroSprite::create();
    addChild(_hero_sprite);
    _hero_sprite->setAnchorPoint(Vec2(1, 0));
    _hero_sprite->setPosition(stake_sprite->getContentSize().width - 20, STAKE_HEIGHT);
}

void GameLayer::stickCollapseEndCall(Node* node)
{
    int hero_x = _hero_sprite->getPositionX();
    int stick_x = _cur_stick_sprite->getPositionX();
    int distance = stick_x - hero_x + _cur_stick_sprite->getContentSize().height;
    _hero_sprite->run(distance, CallFuncN::create(CC_CALLBACK_1(GameLayer::heroRunEndCall, this)));
}

void GameLayer::heroRunEndCall(Node* node)
{
    StakeSprite* next_stake_sprite = _stake_sprites.at(_cur_stake_index + 1);
    int min_x = next_stake_sprite->getPositionX();
    int max_x = next_stake_sprite->getPositionX() + next_stake_sprite->getContentSize().width;
    if(_hero_sprite->getPositionX() >= min_x and _hero_sprite->getPositionX() <= max_x)
    {
        ++_cur_stake_index;
        move();
        setScore(_score + 1);
        refreshScore();
    }else{
        _hero_sprite->fall();
        gameOver();
    }
}

void GameLayer::move()
{   
    auto stake_sprite = _stake_sprites.at(_cur_stake_index);
    _move_distance = stake_sprite->getPositionX() - 20;
    _stake_max_x = _stake_x + _move_distance;
    addStakes();
    _stake_x -= _move_distance;
    auto delay_time = DelayTime::create(0.03);
    auto move_call = CallFuncN::create(CC_CALLBACK_1(GameLayer::moveCall, this));
    auto move_sequence = Sequence::create(delay_time, move_call, NULL);
    _move_action = RepeatForever::create(move_sequence);
    runAction(_move_action);
}

void GameLayer::moveCall(Node* node)
{
    int distance = _move_distance >= 5 ? 5 : _move_distance;
    _hero_sprite->setPositionX(_hero_sprite->getPositionX() - distance);
    int stake_count = _stake_sprites.size();
    for (int i = 0; i < stake_count; ++i) 
    {
        auto stake_sprite = _stake_sprites.at(i);
        stake_sprite->setPositionX(stake_sprite->getPositionX() - distance);
        if(stake_sprite->getPositionX() + stake_sprite->getContentSize().width < 0)
        {
            stake_sprite->removeFromParent();
            _stake_sprites.erase(i);
            --stake_count;
            --i;
            --_cur_stake_index;
        }
    }
    int stick_count = _stick_sprites.size();
    for (int i = 0; i < stick_count; ++i) 
    {
        auto stick_sprite = _stick_sprites.at(i);
        stick_sprite->setPositionX(stick_sprite->getPositionX() - distance);
         if(stick_sprite->getPositionX() + stick_sprite->getContentSize().height < 0)
        {
            stick_sprite->removeFromParent();
            _stick_sprites.erase(i);
            --stick_count;
            --i;
        }

    }
    _move_distance -= distance;
    if(0 == _move_distance)
    {
        moveEnd();
        stopAction(_move_action);
    }
}

void GameLayer::moveEnd()
{
    _game_status = GameStatus::STAND;
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
    if(_game_status != GameStatus::STAND)
    {
        return  false;
    }
    auto i = _stake_sprites.begin();
    while(i != _stake_sprites.end())
    {
        auto stake_sprite = *i;
        if (_hero_sprite->getPositionX() >= stake_sprite->getPositionX() && _hero_sprite->getPositionX() <= stake_sprite->getPositionX() + stake_sprite->getContentSize().width)
        {
            auto stick_sprite = StickSprite::create();
            addChild(stick_sprite);
            stick_sprite->setAnchorPoint(Vec2(1, 0));
            stick_sprite->setPosition(stake_sprite->getPositionX() + stake_sprite->getContentSize().width, stake_sprite->getContentSize().height - stick_sprite->getContentSize().width);
            stick_sprite->grow();
            _cur_stick_sprite = stick_sprite;
            _stick_sprites.pushBack(stick_sprite);
            break;
        }
        ++i;
    }
    return  true;
}

void GameLayer::setScore(int score)
{
    _score = score;
}

void GameLayer::refreshScore(bool is_need_create /* = false*/)
{
    auto text = "score:" + std::to_string(_score);
    if(is_need_create)
    {
        _score_label = Label::createWithSystemFont(text, "Marker Felt" , 23);
        addChild(_score_label);
        _score_label->setAnchorPoint(Vec2(0, 1));
        _score_label->setPosition(20, getContentSize().height);
    }else
    {
        _score_label->setString(text);
    }
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    _cur_stick_sprite->stopGrow();
    _cur_stick_sprite->collapse(CallFuncN::create(CC_CALLBACK_1(GameLayer::stickCollapseEndCall, this)));
    _game_status = GameStatus::MOVE;
}

void GameLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    onTouchEnded(touch, unused_event);
}