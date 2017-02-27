#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "LayerColorScene.h"

#include<ctime>
#include<cstdio>
#include<cstdlib>
USING_NS_CC;

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
	
	auto pcloseitem=MenuItemImage::create("closenormal.png","closeselected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
	pcloseitem->setPosition(Point(Director::getInstance()->getWinSize().width-20,20));
	auto pmenu=Menu::create(pcloseitem,NULL);
	pmenu->setPosition(Point::ZERO);
	anode->addChild(pmenu,1);
	
	auto size=Director::getInstance()->getWinSize();
	
	auto l=LabelTTF::create("This is main scene !\n\nhello world\nhello world","arial",24);
	l->setPosition(Point(size.width/2,size.height/2+50));
	this->addChild(l,0);
	
	auto label=Label::createWithTTF("EXIT","fonts/Marker Felt.ttf",18);
	auto item=MenuItemLabel::create(label,this,menu_selector(HelloWorld::close));
	auto mm=Menu::create(item,NULL);
	mm->alignItemsVertically();
	mm->setPosition(Point(20,size.height-20));
	this->addChild(mm);
	
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(LayerColorScene::createScene());
}

void HelloWorld::close(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

