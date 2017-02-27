#ifndef __HelloWorld__HPSprite__
#define __HelloWorld__HPSprite__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class HPSprite; 
class HPSprite:public cocos2d::CCSprite{
public:
	void myInit();
//	static HPSprite* HPSpriteInit();
	virtual ~HPSprite();
	void setSprite(Sprite * sprite);
	int hp;
	CCSprite* main;
//private:
};
#endif

