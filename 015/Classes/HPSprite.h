#ifndef __HelloWorld__HPSprite__
#define __HelloWorld__HPSprite__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class HPSprite; 
class HPSprite:public cocos2d::CCSprite{
public:
	void myInit();
	virtual ~HPSprite();
	void setSprite(Sprite * sprite);
	int id;
	//enemy
	int hp;
	int fromx;
	int fromy;
	int tox;
	int toy;
	int speed;
	int hasgone;
	//tower
	int xx;
	int yy;
	int damage;
	int range;
	int lv;
	int worth;
	
	CCSprite* main;
};
#endif

