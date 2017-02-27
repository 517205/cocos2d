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
	
	
	MenuItemFont::setFontName("fixedsys");
	MenuItemFont::setFontSize(36);
	
	auto item1=MenuItemFont::create("rotate",this,menu_selector(HelloWorld::rotate));
	item1->setColor(Color3B(255,0,0));
	auto item2=MenuItemFont::create("move",this,menu_selector(HelloWorld::mv));
	item2->setColor(Color3B(255,255,0));
	auto item3=MenuItemFont::create("scale",this,menu_selector(HelloWorld::scale));
	item3->setColor(Color3B(0,255,0));
	auto item4=MenuItemFont::create("rotateforever",this,menu_selector(HelloWorld::forever));
	item4->setColor(Color3B(255,0,255));
	auto item5=MenuItemFont::create("jump",this,menu_selector(HelloWorld::jump));
	item5->setColor(Color3B(0,255,255));
	auto menu2=Menu::create(item1,item2,item3,item4,item5,NULL);
	menu2->alignItemsVertically();
	menu2->setPosition(Point(s.width-50,85));
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
	auto mvby=MoveBy::create(1.5,Point(-Director::getInstance()->getWinSize().width,-Director::getInstance()->getWinSize().height));
	sp2->runAction(mvby);
}

void HelloWorld::rotate(Ref* pSender)
{
	auto sp2=Sprite::create("body1.png");
	sp2->setPosition(Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2));
	sp2->setAnchorPoint(Point(0,0));
	this->addChild(sp2,0);
	auto rotate=RotateBy::create(.75,360);
	auto hide=Hide::create();
	auto seq=Sequence::create(rotate,hide,NULL);
	sp2->runAction(seq);
}

void HelloWorld::scale(Ref* pSender)
{
	auto sp2=Sprite::create("bodystuck.png");
	sp2->setPosition(Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2-50));
	this->addChild(sp2,0);
	auto scale1=ScaleTo::create(1.5,10.0);
	auto scale2=ScaleTo::create(1.0,.5);
	
	auto seq=Sequence::create(scale1,DelayTime::create(0.5),scale2,NULL);
	sp2->runAction(seq);
}
void HelloWorld::forever(Ref* pSender)
{
	auto sp2=Sprite::create("geomcircle.png");
	sp2->setPosition(Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2+50));
	this->addChild(sp2,2);
	auto rotate=RotateBy::create(5,360);
	auto repeat=RepeatForever::create(rotate);
	sp2->runAction(repeat);
}
void HelloWorld::jump(Ref* pSender)
{
	auto sp2=Sprite::create("windowmarker.png");
	sp2->setPosition(Point(Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height/2));
	this->addChild(sp2,0);
	auto jump=JumpTo::create(1.5,Point(0,0),100,4);
	sp2->runAction(jump);
}

void HelloWorld::close(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

