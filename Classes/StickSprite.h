//
//  StickSprite.h
//  StickHero
//
//  Created by bzx-mac on 7/10/15.
//
//

#ifndef __StickHero__StickSprite__
#define __StickHero__StickSprite__

#include <stdio.h>

USING_NS_CC;

class StickSprite:public Sprite
{
public:
    static StickSprite* create();
    void grow();
    void stopGrow();
    void addHeight(Node* node);
    void loadBody();
    void collapse(CallFuncN* end_call_fun);
private:
    Action* _grow_action;
    LayerColor* _body;
};

#endif /* defined(__StickHero__StickSprite__) */
