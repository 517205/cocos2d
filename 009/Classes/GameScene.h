#ifndef __HelloWorld__GameScene_H__
#define __HelloWorld__GameScene_H__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void back(cocos2d::Ref* pSender);
    CREATE_FUNC(GameScene);
};

#endif
