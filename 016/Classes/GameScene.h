#ifndef __HelloWorld__GameScene_H__
#define __HelloWorld__GameScene_H__

#include <iostream>
#include "cocos2d.h"
#include "HPSprite.h"
#include "extensions/cocos-ext.h"
#include <string>
using namespace cocos2d;
USING_NS_CC_EXT;
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    bool myInit(void);
    
    void endbegin(void);
    void resume(cocos2d::Ref* pSender);
    void restart(cocos2d::Ref* pSender);
    void back(cocos2d::Ref* pSender);
    void die(void);
    void menu(cocos2d::Ref* pSender);
    
    void save(cocos2d::Ref* pSender);
    void accel(cocos2d::Ref* pSender,Control::EventType controlEvent);
    void pause_resume(cocos2d::Ref* pSender,Control::EventType controlEvent);
    
    void towersell(cocos2d::Ref* pSender);
    void towerup(cocos2d::Ref* pSender);
    
    void newenemy(int id);
    void newtower(int xx,int yy,int id);
    
    double enemyhpfunc(int wav);
    
    void mainmove(Node* node,HPSprite *sp);
    void entry(Node* node,HPSprite *sp);
    
    bool iscollision(Sprite *s1,Sprite *s2);
    
    void shownews(char a[],int t);
    void newsclear();
    
    void save_init();
    
    void shoot(float delta);
    void updata(float delta);
    
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
	void touchmove(Touch *touch,Event *pEvent);
	void touchend(Touch *touch,Event *pEvent);
    bool playertouch(Touch *touch,Event *pEvent);
    
    CREATE_FUNC(GameScene);
private:
	Node *anode;
	Sprite *player;
	Sprite *no1;
	Sprite *no2;
	Sprite *no3;
	Sprite *no4;
    Menu *mb;
    Menu *ms;
    Menu *mselect;
    LabelAtlas *news;
    LabelAtlas *lmoney;
    LabelAtlas *lwave;
    LabelAtlas *llife;
    LabelAtlas *tmoneyup;
    LabelAtlas *tmoneysell;
    LabelAtlas *tinfo;
    Layer *lm;
    Layer *lwin;
    Layer *lselect;
    __Array *enemy;
    __Array *tower;
    DrawNode* drawnode;
    DrawNode* drawbullet;
    char mup[10];
    char msell[10];
    double x;
    double y;
};

#endif
