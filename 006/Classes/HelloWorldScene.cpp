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
	MenuItemFont::setFontSize(24);
	
	auto dicecount1=LabelAtlas::create("0123456789","myttf_cmd_48x54_number.png",48,54,'0');
//	auto dicecount1=LabelAtlas::create("0123456789","myttf.png",48,54,'0');
	dicecount1->setPosition(Point(0,s.height/2));
	dicecount1->setString("0123456789");
	dicecount1->setScale(1.0);
	this->addChild(dicecount1);
	/*
	auto item1=MenuItemFont::create("add");
	item1->setTarget(this,menu_selector(HelloWorld::add));
	auto item2=MenuItemFont::create("minus");
	item2->setTarget(this,menu_selector(HelloWorld::minus));
	auto menu=Menu::create(item1,item2,NULL);
	menu->setPosition(Point(s.width-30,s.height-30));
	menu->alignItemsVertically();
	this->addChild(menu);
	
	*/
	return true;
}
/*
void HelloWorld::add(Ref* pSender)
{
	dicecount1->setString("0");
		
}
void HelloWorld::minus(Ref* pSender)
{
	dicecount1->setString("1");
}
*/
void HelloWorld::close(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

