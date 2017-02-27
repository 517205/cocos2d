#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void option(cocos2d::Ref* pSender);
    void start(cocos2d::Ref* pSender);
    void quit(cocos2d::Ref* pSender);
    void help(cocos2d::Ref* pSender);
    void about(cocos2d::Ref* pSender);
    void back(cocos2d::Ref* pSender);
	Menu *mainmenu;
	Layer *lmm;
	Layer *layeroption;
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
