#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void start(cocos2d::Ref* pSender);
	void back(cocos2d::Ref* pSender);
	void quit(cocos2d::Ref* pSender);
	
    void option(cocos2d::Ref* pSender);
    void help(cocos2d::Ref* pSender);
    void about(cocos2d::Ref* pSender);
    
    void musicchange(cocos2d::Ref* pSender);
    void soundchange(cocos2d::Ref* pSender);
    void fpschange(cocos2d::Ref* pSender);
    
  //  void musicplay(cocos2d::Ref* ref);
    void musicplay(void);
    
    
private:
	Menu *mainmenu;
	
	Layer *lmm;
	Layer *layeroption;
	Layer *layerabout;
	Layer *layerhelp;
	
	LabelTTF *labelsound;
	LabelTTF *labelmusic;
	LabelTTF *labelfps;
	
	
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
