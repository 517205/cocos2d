#ifndef __HelloWorld__GameScene_H__
#define __HelloWorld__GameScene_H__

#include <iostream>
#include "cocos2d.h"
#include "HPSprite.h"
using namespace cocos2d;
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void endbegin(void);
    void resume(cocos2d::Ref* pSender);
    void restart(cocos2d::Ref* pSender);
    void back(cocos2d::Ref* pSender);
    void goto2(cocos2d::Ref* pSender);
    void gover(void);
    void win(void);
    void menu(cocos2d::Ref* pSender);
    
    bool iscollision(Sprite *s1,Sprite *s2);
    
    void timer(float delta);
    void shoot(float delta);
    void updata(float delta);
    void enemyshoot(float delta);
    void bg(float delta);
    void enemyloop(float delta);
    void createboss(float delta);
    void gift(float delta);
    
    void releasebomb(cocos2d::Ref* pSender);
    void notimmume(void);
    void die(void);
    
    void newenemy_small(void);
    void newboss(void);
    void blast(double x,double y);
    void rm(Node *sp);
    
    void musicplay(void);
    
    
    /*
    void newenemy(float delta);
    void newfood(float delta);
    void gameoversound(void);
    void getfoodsound(void);
    void enemymove(cocos2d::Node *pSender);
    */
	void empty(Touch *touch,Event *pEvent);
    bool playertouch(Touch *touch,Event *pEvent);
    
    CREATE_FUNC(GameScene);
private:
	
	Node *anode;
	Sprite *player;
	Sprite *boss;
	Sprite *GIFT;
    Menu *mb;
    Layer *lm;
    Layer *lover;
    Layer *lwin;
    LabelAtlas *scorelabel;
    LabelAtlas *timelabel;
    LabelAtlas *bomblabel;
    LabelAtlas *lifelabel;
    __Array *playerbullet;
    __Array *enemybullet;
    __Array *enemy;
    double x;
    double y;
    bool isgame=true;
    bool isboss=false;
    bool isimmume=false;
    bool isgift=false;
    int bosslife=150;
};

#endif
