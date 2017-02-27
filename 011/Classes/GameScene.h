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
    void gover(cocos2d::Ref* pSender);
    void endbegin(void);
    void resume(cocos2d::Ref* pSender);
    void restart(cocos2d::Ref* pSender);
    
    
    void up(cocos2d::Ref* pSender);
    void down(cocos2d::Ref* pSender);
    void right(cocos2d::Ref* pSender);
    void left(cocos2d::Ref* pSender);
    
    void updata(float delta);
    void newenemy(float delta);
    
    void musicplay(void);
    void gameoversound(void);
    
//    bool iscollision(Point p1,float x1,float y1,Point p2,float x2,float y2);
    bool iscollision(Sprite *s1,Sprite *s2);
    void enemymove(cocos2d::Node *pSender);
    CREATE_FUNC(GameScene);
private:
	
	Node *anode;
	
    Menu *mb;
    Layer *lm;
    Layer *lover;
    Sprite *player;
//    Sprite *enemy;
    __Array *enemyarray;
    double x;
    double y;
    bool isgame=true;
};

#endif
