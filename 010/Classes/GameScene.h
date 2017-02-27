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
    void menu(cocos2d::Ref* pSender);
    void over(cocos2d::Ref* pSender);
    void resume(cocos2d::Ref* pSender);
    
    void up(cocos2d::Ref* pSender);
    void down(cocos2d::Ref* pSender);
    void right(cocos2d::Ref* pSender);
    void left(cocos2d::Ref* pSender);
    
    void updata(float delta);
    bool iscollision(Point p1,float x1,float y1,Point p2,float x2,float y2);
    void enemymove(cocos2d::Node *pSender);
    CREATE_FUNC(GameScene);
private:
    Menu *mb;
    Layer *lm;
    Sprite *player;
    Sprite *enemy;
    
    double x;
    double y;
};

#endif
