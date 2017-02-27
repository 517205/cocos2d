#ifndef __HelloWorld__LayerColorScene_H__
#define __HelloWorld__LayerColorScene_H__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class LayerColorScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void change(cocos2d::Ref* pSender);
    CREATE_FUNC(LayerColorScene);
};

#endif
