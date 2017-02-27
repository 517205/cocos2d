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
	
	auto item2=MenuItemFont::create("move",this,menu_selector(HelloWorld::mv));
	item2->setColor(Color3B(255,255,0));
	
	auto menu2=Menu::create(item2,NULL);
	menu2->alignItemsVertically();
	menu2->setPosition(Point(s.width-50,85));
	this->addChild(menu2);

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

void HelloWorld::close(Ref* pSender)
{
	auto s=Director::getInstance()->getWinSize();
	auto layer=LayerColor::create(Color4B(0,0,255,127),250,150);
	layer->ignoreAnchorPointForPosition(false);
	layer->setPosition(Point(s.width/2,s.height/2));
	this->addChild(layer,2);
	auto l=Label::createWithTTF("Are you sure to quit ?","fonts/Marker Felt.ttf",26);
	l->setPosition(Point(125,75+20));
	layer->addChild(l,3);
	MenuItemFont::setFontSize(32);
	auto item1=MenuItemFont::create("YES     ",this,menu_selector(HelloWorld::quit));
	auto item2=MenuItemFont::create("NO",this,menu_selector(HelloWorld::regret));
	auto mn=Menu::create(item1,item2,NULL);
	mn->alignItemsHorizontally();
	mn->setPosition(Point(125,75-40));
	layer->addChild(mn,3);
	MenuItemFont::setFontSize(36);
}
void HelloWorld::regret(Ref* pSender)
{
}
void HelloWorld::quit(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}
