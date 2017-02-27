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
    void gover(void);
    void endbegin(void);
    void resume(cocos2d::Ref* pSender);
    void restart(cocos2d::Ref* pSender);
    
    
    void up(cocos2d::Ref* pSender);
    void down(cocos2d::Ref* pSender);
    void right(cocos2d::Ref* pSender);
    void left(cocos2d::Ref* pSender);
    
    void timer(float delta);
    void updata(float delta);
    void newenemy(float delta);
    void newfood(float delta);
    
    void musicplay(void);
    void gameoversound(void);
    void getfoodsound(void);
    
    bool iscollision(Sprite *s1,Sprite *s2);
    void enemymove(cocos2d::Node *pSender);
    
    void empty(Touch *touch,Event *pEvent);
    bool playertouch(Touch *touch,Event *pEvent);
    
    CREATE_FUNC(GameScene);
private:
	
	Node *anode;
	
    Menu *mb;
    Layer *lm;
    Layer *lover;
    LabelAtlas *timelabel;
    LabelAtlas *scorelabel;
    Sprite *player;
    __Array *enemyarray;
    __Array *foodarray;
    double x;
    double y;
    bool isgame=true;
};

#endif
