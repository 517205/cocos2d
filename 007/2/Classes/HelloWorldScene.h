#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	
    virtual bool init();
    
    void mv(cocos2d::Ref* pSender);
	void rotate(cocos2d::Ref* pSender);
	void scale(cocos2d::Ref* pSender);
	void forever(cocos2d::Ref* pSender);
	void jump(cocos2d::Ref* pSender);
    void close(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
