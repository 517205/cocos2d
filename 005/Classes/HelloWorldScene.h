#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	
    virtual bool init();
    
    void close(cocos2d::Ref* pSender);
    void musicplay(Ref *ref);
    void musicstop(Ref *ref);
    void musicpause(Ref *ref);
    void musicresume(Ref *ref);
    
    void effectplay(Ref *ref);
    void effectstop(Ref *ref);
    void effectpause(Ref *ref);
    void effectresume(Ref *ref);
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
