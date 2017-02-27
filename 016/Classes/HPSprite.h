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
	int hpfull;
	int fromx;//eg 480
	int fromy;
	int tox;
	int toy;
	int speed;
	int hasgone;
	double hasgonetmp;
	int cost;
	bool isinrange;
	//tower
	int xx;//eg 10
	int yy;
	int damage;
	int range;
	int lv;
	int worth;
	int firerate;//how many 0.05sec
	LabelAtlas* lvlabel;
	
	CCSprite* main;
};
#endif

