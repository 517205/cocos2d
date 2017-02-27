#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include<ctime>
#include<cstdio>
#include<cstdlib>

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

unsigned int num=0;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool HelloWorld::init()
{
//	MessageBox("welcome here!\n","Alert");
	if(!Layer::init())
	{
		return false;
	}
	auto anode=Node::create();
	this->addChild(anode,0);
	
	auto s=Director::getInstance()->getWinSize();
	
	auto label=Label::createWithTTF("EXIT","fonts/Marker Felt.ttf",18);
	auto item=MenuItemLabel::create(label,this,menu_selector(HelloWorld::close));
	auto mm=Menu::create(item,NULL);
	mm->alignItemsVertically();
	mm->setPosition(Point(20,s.height-20));
	this->addChild(mm,1);
	
	auto sp=Sprite::create("bgblack.png");
	sp->setPosition(Point(s.width/2,s.height/2));
	this->addChild(sp,0);
	
	auto item1=MenuItemFont::create("move",this,menu_selector(HelloWorld::mv));
	item1->setColor(Color3B(255,255,0));
	auto menu2=Menu::create(item1,NULL);
	menu2->alignItemsVertically();
	menu2->setPosition(Point(s.width-30,20));
	this->addChild(menu2);
	/*
	auto sp2=Sprite::create("body.png");
	sp2->setPosition(Point(s.width/2,s.height/2));
	this->addChild(sp2,0);
	auto mvby=MoveTo::create(1.0,Point(0,0));
	sp2->runAction(mvby);
	*/
	return true;
}

void HelloWorld::mv(Ref* pSender)
{
	auto sp2=Sprite::create("body.png");
	sp2->setPosition(Point(Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height));
	this->addChild(sp2,0);
	auto mvby=MoveTo::create(1.5,Point(0,0));
	sp2->runAction(mvby);
}

void HelloWorld::close(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

